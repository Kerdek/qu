#ifndef H_06210ABB_1BC2_4906_A838_6EC2CB1BEBF0
#define H_06210ABB_1BC2_4906_A838_6EC2CB1BEBF0

/*
 * <expr-infix-operator-builtin> ::= <expr-infix-op-builtin>
 *                         | <decl-id>
 */

namespace uwu::parse
{

template<
    typename Caret>
    auto expr_infix_operator_builtin(
        Caret &caret)
    -> char
{    
    auto op_char = peek(caret);
    advance(caret);
    switch(op_char)
    {
        case plus:
            
        default:
            return 0;
    }
}

}

#endif