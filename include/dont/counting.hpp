#pragma once

#include "dont/common.hpp"

namespace dont
{

template <typename IntT, IntT... Is> struct IntegerSequence
{
  static constexpr auto size() { return sizeof...(Is); };
};

template <size_t... Is> using index_sequence_t = IntegerSequence<size_t, Is...>;

namespace detail
{

template <typename IntT, size_t N, size_t I = 0, typename Prev = IntegerSequence<IntT>> struct MakeIntegerSequence;

template <typename IntT, size_t N, size_t I, IntT... Is>
struct MakeIntegerSequence<IntT, N, I, IntegerSequence<IntT, Is...>>
    : MakeIntegerSequence<IntT, N, I + 1, IntegerSequence<IntT, Is..., I>>
{};

template <typename IntT, size_t N, IntT... Is> struct MakeIntegerSequence<IntT, N, N, IntegerSequence<IntT, Is...>>
{
  using type = IntegerSequence<IntT, Is...>;
};

}  // namespace detail

template <typename IntT, size_t N, size_t I = 0> struct MakeIntegerSequence : detail::MakeIntegerSequence<IntT, N, I>
{};

template <typename IntT, size_t N> using make_integer_sequence_t = typename MakeIntegerSequence<IntT, N, 0>::type;

template <size_t N> using make_index_sequence_t = typename MakeIntegerSequence<size_t, N, 0>::type;

}  // namespace dont