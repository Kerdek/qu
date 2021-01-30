#ifndef H_E7EF5311_4FFD_4E0E_8DBD_3ABC6FF0FD59
#define H_E7EF5311_4FFD_4E0E_8DBD_3ABC6FF0FD59

#include <uwu/diagnostic.hpp>

#include <tuple>

#include <ted/same.hpp>

namespace uwu::parse
{

bool check_operator(
    const char *&caret)
{
    return *caret;
}

template<
    typename Caret,
    typename PostfixExpression,
    typename InfixOperator>
auto expr_infix(
    Caret &caret,
    PostfixExpression &top_operand,
    InfixOperator &top_operator)
    -> auto
{
    for(;;)
    {
        auto next_operator = parse_operator(
            caret);

        const auto order = operator_order(
            top_operator,
            next_operator);

        if(!order)
        {
            diagnostic d;

            d << "Greek to me mate."

            throw same(d);
        }

        const auto association = operator_association(
            top_operator,
            next_operator);

        const auto precedence = operator_precedence(
            order,
            association);

        if(precedence)
        {
            auto next_operand = parse_operand(
                caret);

            handle_expr_infix(
                expr_infix(
                    caret,
                    same(next_operator),
                    expr_postfix(
                        caret)));
        }
        else
        {
            return make_tuple(
                top_operand,
                top_operator);
        }
    }
}

}

#include <ted/nosame.hpp>

#endif