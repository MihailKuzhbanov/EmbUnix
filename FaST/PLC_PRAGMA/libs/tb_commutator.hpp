////////////////////////////////////////////////////////////////////////////////
// <@meta=.metablank>
////////////////////////////////////////////////////////////////////////////////
# ifndef TB_COMMUTATOR_INCLUDED_
#  define TB_COMMUTATOR_INCLUDED_

# include <bits/stdc++.h>

# include <array>
# include <iostream>
# include <map>
# include <memory>
# include <string>
# include <vector>

# include "../include/thirdparty/json.hpp"

using json=nlohmann::json;

namespace threadbone {

typedef size_t Exit_t;                                            // exit status

// Связь по имени
struct ChLinkByName {
    uint src_ch_idx;
    uint dst_ch_idx;
    std::string dst_name;
};

// Связь по ID
struct ChLinkById {
    uint src_ch_idx;
    uint dst_ch_idx;
    uint dst_id;
};

typedef std::vector<ChLinkByName>                TPortLinks;
typedef std::map<std::string, TPortLinks>        TSwTabByName;
typedef std::vector<std::vector<ChLinkById>>     TSwTabById;
typedef std::map<std::string, std::vector<uint>> TUsageMap;

/*............................................................................*/
template < typename TChannel, typename TPort >
class Commutator {

    public:
        typedef std::map<std::string, TPort> TPortMap;

    private:
        TPortMap & m_src;
        TPortMap & m_dst;
        TSwTabByName m_swtab_by_name;
        TSwTabById   m_swtab;
        std::map<std::string,uint> m_src_bind;    // связка: ключ (имя) <-> ID
        std::map<std::string,uint> m_dst_bind;    // связка: ключ (имя) <-> ID
        std::vector<TPort*> m_src_port;
        std::vector<TPort*> m_dst_port;
        std::vector<std::unique_ptr<std::vector<TChannel>>> m_dst_buf;
        std::vector<bool> m_dst_updated;
        std::vector<std::string> m_log_src_unknown;
        std::vector<std::string> m_log_dst_unknown;
        std::vector<std::string> m_log_dual_purpose;
        TUsageMap m_log_src_usage;
        TUsageMap m_log_dst_usage;
        json m_state;

    public:
        Commutator(
            TPortMap & src,
            TPortMap & dst,
            TSwTabByName const & swtab_by_name);
        Commutator(
            TPortMap & src,
            TPortMap & dst,
            json const & swtab_by_name);
        inline TSwTabByName const & get_swtab_by_name() const;
        inline TSwTabById const & get_swtab_by_id() const;
        inline std::vector<std::string> const & get_log_src_unknown() const;
        inline std::vector<std::string> const & get_log_dst_unknown() const;
        inline std::vector<std::string> const & get_log_dual_purpose() const;
        inline TUsageMap const & get_log_src_usage() const;
        inline TUsageMap const & get_log_dst_usage() const;
        Exit_t step(int64_t wait);
};

/*............................................................................*/
template < typename TChannel, typename TPort >
Commutator<TChannel,TPort>::Commutator (
    TPortMap & src,
    TPortMap & dst,
    TSwTabByName const & swtab
):
    m_src(src),
    m_dst(dst),
    m_swtab_by_name(),
    m_swtab(),
    m_src_port(1, nullptr),
    m_dst_port(1, nullptr),
    m_dst_buf(1),
    m_dst_updated(1, false),
    m_log_src_unknown(),
    m_log_dst_unknown(),
    m_log_dual_purpose(),
    m_log_src_usage(),
    m_log_dst_usage(),
    m_state()
{
    m_state["bind"]["src"]  = nullptr;
    m_state["bind"]["dst"]  = nullptr;
    m_state["usage"]["src"] = nullptr;
    m_state["usage"]["dst"] = nullptr;
    m_state["undef"]["src"] = nullptr;
    m_state["undef"]["dst"] = nullptr;
    m_state["redef"]["dst"] = nullptr;

    std::string name;
    uint id = 0;
    // Коммутация будет производиться не по именам источников и получателей,
    // а по их локальным (известным только в пределах данного объекта) ID.
    // Присваиваем ID источникам:
    for (const auto & r_src: m_src) {
        m_state["bind"]["src"][r_src.first] = id;
        m_state["usage"]["src"][r_src.first] =
            std::vector<uint>(r_src.second.size(),0);

        m_src_bind[r_src.first] = id;
        m_log_src_usage[r_src.first].resize(r_src.second.size(),0);
        ++id;
    }
    // Присваиваем ID получателям:
    id = 0;
    for (const auto & r_dst: m_dst) {
        name = r_dst.first;
        // Имя не может присутствовать одновременно в src и dst
        if (m_src_bind.count(name) == 0) { // уже добавлено в src
            m_state["bind"]["dst"][r_dst.first] = id;
            m_state["usage"]["dst"][r_dst.first] =
                std::vector<uint>(r_dst.second.size(),0);

            m_dst_bind[name] = id;
            m_log_dst_usage[r_dst.first].resize(r_dst.second.size(),0);
            ++id;
        }
        else {
            // имя порта, который присутствует в src и dst, добавляется в log
            m_state["redef"]["dst"].push_back(name);
            m_log_dual_purpose.push_back(name);
        }
    }
    uint src_id = 0;
    uint src_idx_max = 0;
    uint dst_idx_max = 0;
    m_swtab.resize(m_src_bind.size());
    for (const auto & r_tab: swtab) {
        name = r_tab.first;
        if (m_src_bind.count(name) != 0) {
            // Источник с указанным именем есть среди портов
            src_id = m_src_bind[name];
            src_idx_max = m_src[name].size();
            for (const auto & link: const_cast<TSwTabByName &>(swtab)[name]) {
                if (link.src_ch_idx > src_idx_max) {
                    continue;
                }
                if (m_dst_bind.count(link.dst_name) == 0) {
                    // Потребителя с таким именем нет среди портов
                    m_log_dst_unknown.push_back(link.dst_name);
                    continue;
                }
                dst_idx_max = m_dst[link.dst_name].size();
                if (link.dst_ch_idx > dst_idx_max) {
                    continue;
                }
                m_swtab_by_name[name].push_back(link);
                m_swtab[src_id].push_back(
                    {
                        link.src_ch_idx,
                        link.dst_ch_idx,
                        m_dst_bind[link.dst_name]
                    }
                );
                uint var = m_state["usage"]["src"][name][link.src_ch_idx];
                var++;
                m_state["usage"]["src"][name][link.src_ch_idx] = var;
                var = m_state["usage"]["dst"][link.dst_name][link.dst_ch_idx];
                var++;
                m_state["usage"]["dst"][link.dst_name][link.dst_ch_idx] = var;

                ++m_log_src_usage[name][link.src_ch_idx];
                ++m_log_dst_usage[link.dst_name][link.dst_ch_idx];
            }
        }
        else {
            m_log_src_unknown.push_back(name);
        }
    }
    m_src_port.resize(m_src_bind.size());
    m_dst_port.resize(m_dst_bind.size());
    for (const auto & src_bind: m_src_bind) {
        m_src_port[src_bind.second] = &m_src[src_bind.first];
    }
    for (const auto & dst_bind: m_dst_bind) {
        m_dst_port[dst_bind.second] = &m_dst[dst_bind.first];
    }
    // Выделяем для каждого dst промежуточный буфер хранения
    m_dst_buf.resize(m_dst_port.size());
    for (size_t i=0; i < m_dst_port.size(); i++) {
        m_dst_buf[i] = std::unique_ptr<std::vector<TChannel>>
            (new std::vector<TChannel>((*m_dst_port[i]).size()));
    }
    // Выделяем по флагу готовности на каждый dst
    m_dst_updated.resize(m_dst_port.size(),false);


    std::cout << m_state << std::endl;
}

/*............................................................................*/
template <typename TChannel, typename TPort>
inline TSwTabByName const &
    Commutator<TChannel,TPort>::get_swtab_by_name() const
{
    return m_swtab_by_name;
}

/*............................................................................*/
template <typename TChannel, typename TPort>
inline TSwTabById const &
    Commutator<TChannel,TPort>::get_swtab_by_id() const
{
    return m_swtab;
}

/*............................................................................*/
template <typename TChannel, typename TPort>
inline std::vector<std::string> const &
    Commutator<TChannel,TPort>::get_log_src_unknown() const
{
    return m_log_src_unknown;
}

/*............................................................................*/
template <typename TChannel, typename TPort>
inline std::vector<std::string> const &
    Commutator<TChannel,TPort>::get_log_dst_unknown() const
{
    return m_log_dst_unknown;
}

/*............................................................................*/
template <typename TChannel, typename TPort>
inline std::vector<std::string> const &
    Commutator<TChannel,TPort>::get_log_dual_purpose() const
{
    return m_log_dual_purpose;
}

/*............................................................................*/
template <typename TChannel, typename TPort>
inline TUsageMap const & Commutator<TChannel,TPort>::get_log_src_usage() const {
    return m_log_src_usage;
}

/*............................................................................*/
template <typename TChannel, typename TPort>
inline TUsageMap const & Commutator<TChannel,TPort>::get_log_dst_usage() const {
    return m_log_dst_usage;
}

/*............................................................................*/
template < typename TChannel, typename TPort >
Exit_t Commutator<TChannel,TPort>::step(int64_t wait) {
    bool updated = false;
    std::vector<TChannel> src_buf;
    std::vector<ChLinkById> tab;
    ChLinkById link;
    size_t tab_size;
    std::fill(m_dst_updated.begin(), m_dst_updated.end(), false);
    // Кросс-коммутация. Сгруппирована по источникам.
    size_t i=0;
    while (i < m_src_port.size()) {
        src_buf = (*m_src_port[i]).fetch(updated);
        if (updated) {
            tab = m_swtab[i];
            tab_size = tab.size();
            size_t j=0;
            while (j < tab_size) {
                link = tab[j];
                (*m_dst_buf[link.dst_id])[link.dst_ch_idx] =
                    src_buf[link.src_ch_idx];
                m_dst_updated[link.dst_id] = true;
                ++j;
            }
            (*m_src_port[i]).release();
        }
        ++i;
    }
    size_t cnt = std::count(m_dst_updated.begin(), m_dst_updated.end(), true);
    Exit_t res;
    int64_t nsec = 0;
    int64_t nsec_wr = 0;
    auto start_wr = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::high_resolution_clock::now() - start_wr;
    auto elapsed_wr = std::chrono::high_resolution_clock::now() - start_wr;
    auto start = std::chrono::high_resolution_clock::now();
    // Переписываем dst буферы в dst
    if (cnt) {
        while(1) {
            for (size_t i=0; i < m_dst_updated.size(); i++) {
                if (m_dst_updated[i]) {
                    start_wr = std::chrono::high_resolution_clock::now();
                    res = m_dst_port[i]->write(*(m_dst_buf[i]),0);
                    elapsed_wr = std::chrono::high_resolution_clock::now() - 
                        start_wr;
                    if (res == EXIT_SUCCESS) {
                        m_dst_updated[i] = false;
                        cnt--;
                        if (cnt == 0) {
                            // Все буферы переписаны в dst
                            return EXIT_SUCCESS;
                        }
                    }
                    nsec_wr += std::chrono::duration_cast<std::chrono
                        ::nanoseconds>(elapsed_wr).count();
                }
            }
            elapsed = std::chrono::high_resolution_clock::now() - start;
            // Учитывается только время, проведенное вне ф-ции write
            nsec = std::chrono::duration_cast<std::chrono
                ::nanoseconds>(elapsed).count() - nsec_wr;
            if (nsec > wait*1000) {
                // установить соотв-й код ошибки (неполная коммутация)
                return EXIT_FAILURE;
            }
        }
    }
    // установить соотв-й код ошибки (нет данных для коммутации)
    return EXIT_FAILURE;
}

/*............................................................................*/

}                                                        // namespace threadbone

# endif                                               // TB_COMMUTATOR_INCLUDED_
