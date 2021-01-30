#ifndef H_21FF0F42_FB38_4E21_BA24_A5B43798DDFB
#define H_21FF0F42_FB38_4E21_BA24_A5B43798DDFB

#include <uwu/parse/operator/order.hpp>
#include <uwu/parse/operator/association.hpp>

namespace uwu::parse
{

auto operator_precedence(
    order_kind l,
    association_kind r)
noexcept -> bool
{
    return l == order_kind::before || 
        (l == order_kind::equiv && r == association_kind::right);
}

}

#endif