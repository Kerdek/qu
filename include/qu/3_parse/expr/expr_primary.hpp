#ifndef H_42A960A3_FE80_48B0_AB8E_57F2780098AC
#define H_42A960A3_FE80_48B0_AB8E_57F2780098AC

/*
 * <expr-primary> ::= <expr-paren>
 *                  | <decl-id>
 */

namespace uwu::parse
{

template<
    typename Caret>
auto expr_primary(
    Caret &caret)
    -> decltype(auto)
{
    if(possible_decl_id(caret))
    {
        return handle_expr_primary(
            expr_paren(
                caret));
    }
    else
    {
        return handle_expr_primary(
            decl_id(
                caret));
    }
}

}

#endif