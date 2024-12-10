#pragma once

// Dont
#include "dont/common.hpp"
#include "dont/detail/counting.hpp"

namespace dont
{

/**
 * @brief Holds a pack of digits of type <code>IntT</code> as template arguments
 */
template <typename IntT, IntT... Is> struct IntegerSequence
{
  static constexpr auto size() { return sizeof...(Is); };
};

/**
 * @brief Holds a pack of digits of type <code>size_t</code> as template arguments
 */
template <size_t... Is> using index_sequence_t = IntegerSequence<size_t, Is...>;

/**
 * @brief Creates an <code>IntegerSequence</code> with digits of type <code>IntT</code> that ends at <code>N-1</code>
 * starting from <code>I</code>
 */
template <typename IntT, size_t N, size_t I = 0> struct MakeIntegerSequence : detail::MakeIntegerSequence<IntT, N, I>
{};

/**
 * @brief Creates an <code>IntegerSequence</code> with digits of type <code>IntT</code> that ends at <code>N-1</code>
 * starting from <code>I</code>
 */
template <typename IntT, size_t N> using make_integer_sequence_t = typename MakeIntegerSequence<IntT, N, 0>::type;

/**
 * @brief Creates an <code>IntegerSequence</code> with digits of type <code>size_t</code> that ends at <code>N-1</code>
 * starting from <code>I</code>
 */
template <size_t N> using make_index_sequence_t = typename MakeIntegerSequence<size_t, N, 0>::type;

}  // namespace dont