#ifndef H_21131696_327D_41A7_BE2C_7FBAA7497F9C
#define H_21131696_327D_41A7_BE2C_7FBAA7497F9C

#include <uwu/parse/association_kind.hpp>

namespace uwu::parse
{

template<
    typename Operator>
    association_kind operator_association(
        const Operator &c,
        const Operator &d)
{
    return association_kind::left; // kekw
}

}

#endif