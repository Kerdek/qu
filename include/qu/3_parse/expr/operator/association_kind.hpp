#ifndef H_EA22E85C_B9CA_45EF_AD60_0BA545949527
#define H_EA22E85C_B9CA_45EF_AD60_0BA545949527

namespace uwu::parse
{
    
enum struct association_kind : unsigned char
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

}

#endif