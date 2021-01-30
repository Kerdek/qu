#include <iostream>
#include <cassert>

std::string parse_primary_expression(
    const char *&caret)
{
    std::string result;
    for(;*caret != ' '; ++caret)
    {
        result.push_back(*caret);
    }
    return result;
}

bool check_operator(
    const char *&caret)
{
    return *caret;
}

std::string parse_operator(
    const char *&caret)
{
    ++caret;
    std::string result;
    for(;*caret != ' '; ++caret)
    {
        result.push_back(*caret);
    }
    ++caret;
    return result;
}

enum struct order_kind : int
{
    none,
    before,
    after,
    equiv
};

auto operator&(
    order_kind l,
    order_kind r)
noexcept -> bool
{
    return 
        static_cast<int>(l) & static_cast<int>(r);
}

auto operator!(
    order_kind a)
noexcept -> bool
{
    return a == order_kind::none;
}

auto operator_precedes(
    const std::string &c,
    const std::string &d)
noexcept -> order_kind
{
    auto cled = c <= d;
    auto dlec = d <= c;

    return dlec
        ? cled
            ? order_kind::equiv
            : order_kind::after
        : cled
            ? order_kind::before
            : order_kind::none;
}

enum struct association_kind : int
{
    left,
    right,
    none
};

auto operator!(
    association_kind a)
noexcept -> bool
{
    return a == association_kind::none;
}

association_kind operator_associates(
    const std::string &c,
    const std::string &d)
{
    return association_kind::left;
}

auto operator>(
    order_kind l,
    association_kind r)
noexcept -> bool
{
    return l == order_kind::before || 
        (l == order_kind::equiv && r == association_kind::right);
}

auto parse_binary_expression(
    const char *&caret,
    std::string &top_operator,
    std::string top_operand)
    -> std::string
{
    for(;;)
    {
        if(!check_operator(caret))
        {
            return top_operator + top_operand;
        }

        const std::string next_operator = parse_operator(
            caret);

        const order_kind precedence = operator_precedes(
            top_operator,
            next_operator);
        const association_kind association = operator_associates(
            top_operator,
            next_operator);

        assert(precedence);

        if(precedence > association)
        {
            std::string next_operand = parse_primary_expression(
                caret);
            const std::string tail = parse_binary_expression(
                caret,
                next_operator,
                next_operand);
            top_operand = '(' + top_operand + tail + ')';
        }
        else
        {
            return top_operator + top_operand;
        }
    }
}

int main()
{
    auto str = "A c B a C d D b E c F a G e H";

    auto caret = str;
    auto initial_result = parse_primary_expression(
        caret);
    std::cout << parse_binary_expression(
        caret,
        "0",
        initial_result);

    std::cout << std::endl;

    return 0;
}