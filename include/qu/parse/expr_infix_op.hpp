#ifndef H_022288E4_703A_43AB_90C5_3DE27B0C2710
#define H_022288E4_703A_43AB_90C5_3DE27B0C2710

/*
 * <expr-infix-operator> ::= <expr-infix-op-builtin>
 *                         | <decl-id>
 */

namespace qu::parse
{

template<
    typename Caret>
    auto expr_infix_operator(
        Caret &caret)
{    
    if(possible_decl_id(peek(caret)))
    {
        return handle_expr_infix_operator(
            decl_id(
                caret));
    }
    else
    {
        return handle_expr_infix_operator(
            expr_infix_operator_builtin(
                caret));
    }
}

}

#endif