/*




*/

#ifndef H_868990CF_55AD_4D07_8D5C_B6C48B11CA00
#define H_868990CF_55AD_4D07_8D5C_B6C48B11CA00

#include <ted/iterator.hpp>
#include <ted/contains.hpp>

#include <initializer_list>

namespace qu::token::simple
{

template<
    typename Caret>
    auto is_unit_ws(
        Caret &&caret)
    -> bool
{
    using ted::iterator::peek;

    const auto c = peek(caret);

    return c == space
        || c == tab
        || c == cr
        || c == lf;
}

}

template<
    typename Caret>
    auto is_unit_id(
        Caret &&caret)
    -> bool
{
    using ted::iterator::peek;

    const auto c = peek(caret);

    return c == underscore
        || (c >= begin_id_alpha && c <= end_id_alpha);
}

const auto infix = 
{
    lt,
    gt,
    eq,
    complement,
    pipe,
    amp,
    plus,
    minus,
    times,
    divide,
    modulo,
    negate
};

template<
    typename Caret>
    auto is_unit_infix(
        Caret &&caret)
    -> bool
{
    using ted::iterator::peek;

    contains(
        begin(infix),
        end(infix),
        peek(caret));
}

}

#endif