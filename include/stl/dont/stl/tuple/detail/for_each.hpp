#pragma once

// C++ Standard Library
#include <tuple>
#include <type_traits>

// Dont
#include "dont/common.hpp"
#include "dont/for_each.hpp"

namespace dont::tuple::detail
{

template <size_t I> struct TupleElementAccess
{
  template <typename... Ts> constexpr auto& operator()(::std::tuple<Ts...>& tup) { return ::std::get<I>(tup); }
  template <typename... Ts> constexpr const auto& operator()(const ::std::tuple<Ts...>& tup) const
  {
    return ::std::get<I>(tup);
  }
};

template <typename TupleT, std::size_t... Is>
decltype(auto) reversed(TupleT&& tup, std::integer_sequence<std::size_t, Is...> _)
{
  using InputTupleType = std::remove_reference_t<TupleT>;
  static constexpr std::size_t N = sizeof...(Is);
  return std::forward_as_tuple(std::get<(N - Is - 1)>(std::forward<TupleT>(tup))...);
}

template <typename TupleT> decltype(auto) reversed(TupleT&& tup)
{
  using InputTupleType = std::remove_const_t<std::remove_reference_t<TupleT>>;
  static constexpr std::size_t N = std::tuple_size_v<InputTupleType>;
  return reversed(std::forward<TupleT>(tup), std::make_integer_sequence<std::size_t, N>{});
}

}  // namespace dont::tuple::detail