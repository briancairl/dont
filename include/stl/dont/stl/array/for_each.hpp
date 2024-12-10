#pragma once

// C++ Standard Library
#include <array>

// Dont
#include "dont/common.hpp"
#include "dont/for_each.hpp"

namespace dont::array
{

namespace detail
{

template <size_t I> struct ArrayElementAccess
{
  template <typename T, size_t N> constexpr auto& operator()(T (&arr)[N]) { return arr[I]; }
  template <typename T, size_t N> constexpr const auto& operator()(const T (&arr)[N]) const { return arr[I]; }

  template <typename T, size_t N> constexpr auto& operator()(::std::array<T, N>& arr) { return arr[I]; }
  template <typename T, size_t N> constexpr const auto& operator()(const ::std::array<T, N>& arr) const
  {
    return arr[I];
  }
};

/**
 * @brief Computes size of an array
 */
template <typename... ArrayLikeTs> struct ArraySize;

/**
 * @copydoc ArraySize
 */
template <typename T, size_t N> struct ArraySize<::std::array<T, N>> : Constant<size_t, N>
{};

/**
 * @copydoc ArraySize
 */
template <typename T, size_t N> struct ArraySize<T[N]> : Constant<size_t, N>
{};

/**
 * @copydoc ArraySize
 * @note common size resolution
 */
template <typename FirstArrayT, typename SecondArrayT, typename... OtherArrayTs>
struct ArraySize<FirstArrayT, SecondArrayT, OtherArrayTs...> : ArraySize<FirstArrayT>
{
  static_assert(ArraySize<FirstArrayT>() == ArraySize<SecondArrayT, OtherArrayTs...>(), "array sizes do not match");
};

template <typename... ArrayLikeTs> constexpr auto array_size_v = ArraySize<ArrayLikeTs...>::value;

}  // namespace detail

template <typename UnaryCallableT, typename... ArrayTs> auto for_each(UnaryCallableT&& callable, ArrayTs&&... arrays)
{
  return ::dont::detail::for_each<detail::ArrayElementAccess>(
    _forward<UnaryCallableT>(callable),
    make_index_sequence_t<detail::array_size_v<::dont::remove_const_t<::dont::remove_reference_t<ArrayTs>>...>>{},
    _forward<ArrayTs>(arrays)...);
}

}  // namespace dont::array