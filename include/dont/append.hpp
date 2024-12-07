#pragma once

#include "dont/common.hpp"
#include "dont/conditions.hpp"

namespace dont
{

template<template<typename, typename> class Condition, typename PackLikeT, typename AppendT>
struct AppendIf;


template<template<typename, typename> class Condition, typename PackLikeT, typename AppendT>
using append_if_t = typename AppendIf<Condition, PackLikeT, AppendT>::type;


template<template<typename, typename> class Condition, template<typename...> class PackLike, typename... Ts, typename AppendT>
struct AppendIf<Condition, PackLike<Ts...>, AppendT>
{
    using type = if_else_t<
        Condition<AppendT, PackLike<Ts...>>::value,
        PackLike<Ts..., AppendT>,
        PackLike<Ts...>
    >;
};

template<typename PackLikeT, typename AppendT>
using append_t = typename AppendIf<Identity, PackLikeT, AppendT>::type;

template<typename PackLikeT, typename AppendT>
using set_add_t = typename AppendIf<Invert<IsMember>::eval, PackLikeT, AppendT>::type;

} // namespace dont