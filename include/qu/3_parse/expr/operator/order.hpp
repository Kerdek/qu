#ifndef H_3D3A4CC0_0ADC_44C0_962B_56D113BC84B3
#define H_3D3A4CC0_0ADC_44C0_962B_56D113BC84B3

#include <uwu/parse/order_kind.hpp>

namespace uwu::parse
{
    
template<
    typename Operator>
auto operator_order(
    const Operator &c,
    const Operator &d)
noexcept -> order_kind
{
    auto c_prececes_d = operator_precedes(
        c,
        d);
    auto d_precedes_c = operator_precedes(
        d,
        c);

    return d_precedes_c
        ? c_prececes_d
            ? order_kind::equivalent
            : order_kind::after
        : c_prececes_d
            ? order_kind::before
            : order_kind::none;
}

}

#endif