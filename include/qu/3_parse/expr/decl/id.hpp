#ifndef H_59B5A7F2_23B7_494D_BC37_66EA189C434C
#define H_59B5A7F2_23B7_494D_BC37_66EA189C434C

#include <uwu/diagnostic.hpp>

namespace uwu::parse
{

template<
    typename ExprId>
auto refine_decl_id(
    ExprId &&expr_id)
    -> decltype(auto)
{
    if (is_bool_key(expr_id))
    {
        diagnostic d;

        d << "<bool_key> is not allowed";

        throw same(d);
    }

    return same(expr_id);
}

template<
    typename Caret>
auto decl_id(
    Caret &caret)
    -> decltype(auto)
{
    try
    {
    return handle_decl_id(
        check_decl_id(
            expr_id(
                caret)));
    }
    catch (diagnostic &d)
    {
        d << " in <decl-id>";

        throw;
    }
}

}

#endif