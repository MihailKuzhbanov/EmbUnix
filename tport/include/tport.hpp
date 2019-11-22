////////////////////////////////////////////////////////////////////////////////
// <@meta=.metablank>
////////////////////////////////////////////////////////////////////////////////
# ifndef TPORT_INCLUDED_
#  define TPORT_INCLUDED_

# include <unistd.h>

# include <atomic>
# include <chrono>
# include <iostream>
# include <vector>


namespace tport {

typedef long long Ver_t;
typedef size_t Exit_t;                                          // exit status

/*............................................................................*/
template < typename TChannel >
class TPort {
    private:
        size_t m_num;
        std::atomic_flag m_busy_buf1;
        std::atomic_flag m_busy_buf2;
        std::vector<TChannel> m_buf1;
        std::vector<TChannel> m_buf2;
        Ver_t m_wr_ver_buf1;
        Ver_t m_wr_ver_buf2;
        Ver_t m_wr_ver;
        Ver_t m_rd_ver;
        uint m_fetched;

    public:
        TPort(size_t num);
        size_t size(void) const;
        Exit_t write(const std::vector<TChannel>& data, int64_t wait);
        Exit_t read(std::vector<TChannel>& data);
        Exit_t fetch(std::vector<TChannel>& data);
        Exit_t release(void);
};

/*............................................................................*/
template < typename TChannel >
TPort<TChannel>::TPort(size_t num):
    m_num(num),
    m_buf1(num),
    m_buf2(num),
    m_wr_ver_buf1(0),
    m_wr_ver_buf2(0),
    m_wr_ver(0),
    m_rd_ver(0),
    m_fetched(0)
{

}

/*............................................................................*/
template < typename TChannel >
size_t TPort<TChannel>::size(void) const {
    return m_num;
}

/*............................................................................*/
template < typename TChannel >
Exit_t TPort<TChannel>::write(const std::vector<TChannel>& data, int64_t wait) {
    if (data.size() != m_num) {
        std::cerr << ": wrong vector length (given: " << data.size() <<
        ", must: " << m_num << ")" << std::endl;
        return EXIT_FAILURE;
    }
    // В ф-ции read возможен кратковременный захват обоих буферов для
    // определения буфера с наиболее свежими данными. Поэтому вызываем в
    // бесконечном цикле в надежде, что какой-нибудь из них скоро освободится.
    // Но запустим таймер, чтобы, в случае чего, принудительно выйти из цикла.
    auto start = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    int64_t usec = 0;
    while(1) {
        if (!m_busy_buf1.test_and_set(std::memory_order_seq_cst)) {
            m_wr_ver++;
            m_wr_ver_buf1 = m_wr_ver;
            for (size_t i=0; i < m_num; i++) {
                m_buf1[i] = data[i];
            }
            m_busy_buf1.clear(std::memory_order_seq_cst);
            return EXIT_SUCCESS;
        }
        if (!m_busy_buf2.test_and_set(std::memory_order_seq_cst)) {
            m_wr_ver++;
            m_wr_ver_buf2 = m_wr_ver;
            for (size_t i=0; i < m_num; i++) {
                m_buf2[i] = data[i];
            }
            m_busy_buf2.clear(std::memory_order_seq_cst);
            return EXIT_SUCCESS;
        }
        elapsed = std::chrono::high_resolution_clock::now() - start;
        usec = std::chrono::duration_cast<std::chrono
            ::microseconds>(elapsed).count();
        if (usec > wait) {
            // if (wait > 0) { // при нулевом ожидании, флаги не сбрасываются
            //     m_busy_buf1.clear(std::memory_order_seq_cst);
            //     m_busy_buf2.clear(std::memory_order_seq_cst);
            // }
            return EXIT_FAILURE;
        }
    }
}

/*............................................................................*/
template < typename TChannel >
Exit_t TPort<TChannel>::fetch(std::vector<TChannel>& data) {
    // Пытаемся захватить оба буфера, чтобы определить в каком из них
    // наиболее свежая версия данных. Если не получается, захватываем тот,
    // который свободен.
    if (!m_busy_buf1.test_and_set(std::memory_order_seq_cst)) {
        if (!m_busy_buf2.test_and_set(std::memory_order_seq_cst)) {
            // Удалось захватить оба буфера.
            if (m_wr_ver_buf1 > m_rd_ver || m_wr_ver_buf2 > m_rd_ver) {
                if (m_wr_ver_buf1 > m_wr_ver_buf2) {
                    // Как можно быстрее освобождаем 2-й буфер - в нем менее
                    // свежие данные, нас он не интересует
                    m_busy_buf2.clear(std::memory_order_seq_cst);
                    m_fetched=1;
                    data = m_buf1;
                    m_rd_ver = m_wr_ver_buf1;
                    // освободить m_busy_buf1 методом release
                    return EXIT_SUCCESS;
                }
                else {
                    // Как можно быстрее освобождаем 1-й буфер - в нем менее
                    // свежие данные, нас он не интересует
                    m_busy_buf1.clear(std::memory_order_seq_cst);
                    m_fetched=2;
                    data = m_buf2;
                    m_rd_ver = m_wr_ver_buf2;
                    // освободить m_busy_buf2 методом release
                    return EXIT_SUCCESS;
                }
            }
            else {
                // Более свежих данных, чем уже были прочитаны, ни в одном
                // буфере нет. Освобождаем оба буфера.
                m_busy_buf1.clear(std::memory_order_seq_cst);
                m_busy_buf2.clear(std::memory_order_seq_cst);
                return EXIT_FAILURE;
            }
        }
        // Удалось захватить только 1-й буфер.
        if (m_wr_ver_buf1 > m_rd_ver) {
            m_fetched=1;
            data = m_buf1;
            m_rd_ver = m_wr_ver_buf1;
            // освободить m_busy_buf1 методом release
            return EXIT_SUCCESS;
        }
        m_busy_buf1.clear(std::memory_order_seq_cst);
        return EXIT_FAILURE;
    }
    else if (!m_busy_buf2.test_and_set(std::memory_order_seq_cst)) {
        // Удалось захватить только 2-й буфер.
        if (m_wr_ver_buf2 > m_rd_ver) {
            m_fetched=2;
            data = m_buf2;
            m_rd_ver = m_wr_ver_buf2;
            // освободить m_busy_buf2 методом release
            return EXIT_SUCCESS;
        }
        m_busy_buf2.clear(std::memory_order_seq_cst);
        return EXIT_FAILURE;
    }
    // Не удалось захватить ни одного буфер (маловероятно, т.к.
    // писатель в каждый момент времени захватывает не боее 1-го буфера)
    return EXIT_FAILURE;
}

/*............................................................................*/
template < typename TChannel >
Exit_t TPort<TChannel>::release(void) {
    if (m_fetched == 1) {
        m_busy_buf1.clear();
        m_fetched = 0;
        return EXIT_SUCCESS;
    }
    else if (m_fetched == 2) {
        m_busy_buf2.clear();
        m_fetched = 0;
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

/*............................................................................*/
template < typename TChannel >
Exit_t TPort<TChannel>::read(std::vector<TChannel>& data) {
    if (data.size() != m_num) {
        std::cerr << ": wrong vector length (given: " << data.size() <<
        ", must: " << m_num << ")" << std::endl;
        return EXIT_FAILURE;
    }
    std::vector<TChannel>& buf = m_buf1;
    if (fetch(buf) == EXIT_SUCCESS) {
        for (size_t i=0; i < m_num; i++) {
            data[i] = buf[i];
        }
        return release(); //
    }
    return EXIT_FAILURE;
}

}  // namespace tport
# endif  // TPORT_INCLUDED_
