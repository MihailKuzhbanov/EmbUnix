//////////////////////////////////////////////////////////////////////////////
// <@meta=.metablank>
//////////////////////////////////////////////////////////////////////////////
# ifndef IEC_INCLUDED_
#  define IEC_INCLUDED_

# include <vector>
# include <string>

namespace IEC {

// Каждое поле структуры выровнено по границе 64 бита, вне зависимости от
// разрядности архитектуры и размера поля.
//struct Channel {
//    alignas(8) U64 value;
//    alignas(8) U16 quality;
//    alignas(8) U64 timestamp;
//};

typedef struct {
    long double value;
    uint64_t timestamp;
    uint16_t quality;
} Channel;

}                                                               // namespace IEC

# endif                                                         // IEC_INCLUDED_

/*
 * NOTE:
 * long double - 16 байт
 * */
