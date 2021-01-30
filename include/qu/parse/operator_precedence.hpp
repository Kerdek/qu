#ifndef H_21FF0F42_FB38_4E21_BA24_A5B43798DDFB
#define H_21FF0F42_FB38_4E21_BA24_A5B43798DDFB

#include <qu/parse/operator_order.hpp>
#include <qu/parse/operator_association.hpp>

namespace qu::parse
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