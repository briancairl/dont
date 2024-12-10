#pragma once

// C++ Standard Library
#include <tuple>

// Dont
#include "dont/common.hpp"
#include "dont/for_each.hpp"

namespace dont::tuple
{

namespace detail
{

template <size_t I> struct TupleElementAccess
{
  template <typename... Ts> constexpr auto& operator()(::std::tuple<Ts...>& tup) { return ::std::get<I>(tup); }
  template <typename... Ts> constexpr const auto& operator()(const ::std::tuple<Ts...>& tup) const
  {
    return ::std::get<I>(tup);
  }
};

}  // namespace detail

template <typename UnaryCallableT, typename... TupleTs> auto for_each(UnaryCallableT&& callable, TupleTs&&... tups)
{
  return ::dont::for_each<detail::TupleElementAccess>(_forward<UnaryCallableT>(callable), _forward<TupleTs>(tups)...);
}

}  // namespace dont::tuple