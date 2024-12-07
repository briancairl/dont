#pragma once

namespace dont
{

template<typename T, T Value>
struct Constant
{
    static constexpr T value = Value;
    constexpr operator T() const { return Value; }
};

struct True : Constant<bool, true> {};

struct False : Constant<bool, false> {};

template<typename L, typename R>
struct IsSame : False {};

template<typename T>
struct IsSame<T, T> : True {};

template<typename L, typename R>
constexpr bool is_same_v = IsSame<L, R>::value;

template<bool U, typename F, typename S>
struct IfElse;

template<typename F, typename S>
struct IfElse<true, F, S>
{
    using type = F;
};

template<typename F, typename S>
struct IfElse<false, F, S>
{
    using type = S;
};

template<bool U, typename F, typename S>
using if_else_t = typename IfElse<U, F, S>::type;

} // namespace dont