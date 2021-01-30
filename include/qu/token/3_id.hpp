#ifndef H_07FC4573_62BB_453A_BBEB_8FEF8DE11156
#define H_07FC4573_62BB_453A_BBEB_8FEF8DE11156

#include <uwu/diagnostic.hpp>

#include <ted/equal.hpp>

namespace uwu::tokens
{

constexpr const char let_key[] = "let";

template<
    typename Id>
    auto is_let_key(
        Id &&id)
        -> bool
{
    using ted::equal;

    return equal(
        id,
        let_key);
}

template<
    typename Id>
auto refine_qual_id(
    Id &&id)
    -> decltype(auto)
{
    if (is_let_key(id))
    {
        diagnostic d;

        d << "'let' is not allowed";

        throw same(d);
    }

    return same(id);
}

template<
    typename Caret>
auto qual_id(
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