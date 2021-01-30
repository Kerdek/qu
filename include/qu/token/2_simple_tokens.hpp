#ifndef H_D0CB7727_1B4F_49AF_8B15_2094E35D8270
#define H_D0CB7727_1B4F_49AF_8B15_2094E35D8270

#include <uwu/tokens/1_subunits.hpp>

namespace uwu::tokens
{
    
template<
    typename Caret>
    auto ws(
        Caret &&caret)
    -> decltype(auto)
{
    auto begin = caret;
    while(is_ws_unit(caret))
    {
        ws_unit(
            caret);
    }
    auto end = caret;

    return handle_ws(
        same(begin),
        same(end));
}

template<
    typename Caret>
    auto id(
        Caret &&caret)
    -> void
{
    auto begin = caret;
    while(is_id_unit(caret))
    {
        id_unit(
            caret);
    }
    auto end = caret;
    
    return handle_id(
        same(begin),
        same(end));
}

}

#endif