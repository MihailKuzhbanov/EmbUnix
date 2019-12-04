//////////////////////////////////////////////////////////////////////////////
// <@meta=.metablank>
//////////////////////////////////////////////////////////////////////////////

# ifndef TB_AUX_INCLUDED_
#  define TB_AUX_INCLUDED_

# include <atomic>

namespace threadbone {

// Oбертка, добавляющая конструктор копирования и перемещения к std::atomic.
//
// NOTE:
// https://stackoverflow.com/questions/13193484/how-to-declare-a-vector-of-atomic-in-c
template <typename T>
struct watomic {

    std::atomic<T> value;

    watomic()
        :value() {}

    watomic(const std::atomic<T> &a)
        :value(a.load()) {}

    watomic(const watomic &other)
        :value(other.value.load()) {}

    // watomic & operator=(const watomic &other) {
    void operator=(const watomic &other) {
        value.store(other.value.load());
    }

    void operator=(T val) {
      value.store(val);
    }
};

}                                                        // namespace threadbone

# endif                                                      // TB_AUX_INCLUDED_
