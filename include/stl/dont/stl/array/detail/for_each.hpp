#pragma once

// C++ Standard Library
#include <array>

// Dont
#include "dont/common.hpp"
#include "dont/for_each.hpp"

namespace dont::array::detail
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

}  // namespace dont::array::detail