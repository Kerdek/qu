#ifndef H_42A960A3_FE80_48B0_AB8E_57F2780098AC
#define H_42A960A3_FE80_48B0_AB8E_57F2780098AC

/*
 * <expr-primary> ::= <expr-paren>
 *                  | <decl-id>
 *
 * <expr-paren>'s start set is '('
 */

namespace qu::parse
{

template<
    typename Caret>
auto expr_primary(
    Caret &caret)
    -> decltype(auto)
{
    switch(peek(caret))
    {
        case '(':
            return handle_expr_primary(
                expr_paren(
                    caret));
        default:
            return handle_expr_primary(
                decl_id(
                    caret));
    }
}

}

#endif