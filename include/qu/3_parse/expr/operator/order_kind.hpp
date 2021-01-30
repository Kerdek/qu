#ifndef H_0AA7566B_BDAE_4513_9FFF_28E240DF4156
#define H_0AA7566B_BDAE_4513_9FFF_28E240DF4156

namespace uwu::parse
{
    
enum struct order_kind : unsigned char
{
    none,
    before,
    after,
    equivalent
};

auto operator&(
    order_kind l,
    order_kind r)
noexcept -> bool
{
    return static_cast<unsigned char>(l) 
         & static_cast<unsigned char>(r);
}

auto operator!(
    order_kind a)
noexcept -> bool
{
    return a == order_kind::none;
}

}

#endif