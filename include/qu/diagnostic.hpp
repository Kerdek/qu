#ifndef H_E7399E9E_14FF_4BBF_BB18_A69CC8AFCFCF
#define H_E7399E9E_14FF_4BBF_BB18_A69CC8AFCFCF

#include <sstream>

#include <ted/same.hpp>

namespace uwu
{

struct diagnostic
{
    std::stringstream ss;
};

template<
    typename Rhs>
    auto operator<<(
        diagnostic &d,
        Rhs &&rhs)
{
    d.ss << same(rhs);
}

auto what(
    const diagnostic &d)
-> std::string
{
    return d.ss.str();
}

}

#include <ted/nosame.hpp>

#endif