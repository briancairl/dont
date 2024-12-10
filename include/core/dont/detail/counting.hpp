// clang-format off
#pragma once

// Dont
#include "dont/common.hpp"

namespace dont
{
template <typename IntT, IntT... Is> struct IntegerSequence;

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
}  // namespace dont
// clang-format on