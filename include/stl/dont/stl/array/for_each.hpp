#pragma once

// C++ Standard Library
#include <array>

// Dont
#include "dont/stl/array/detail/for_each.hpp"

namespace dont::array
{

/**
 * @brief "Iterates" over <code>arrays...</code> of equal length simultaneously
 */
template <typename UnaryCallableT, typename... ArrayTs> auto for_each(UnaryCallableT&& callable, ArrayTs&&... arrays)
{
  return ::dont::detail::for_each<detail::ArrayElementAccess>(
    _forward<UnaryCallableT>(callable),
    make_index_sequence_t<detail::array_size_v<::dont::remove_const_t<::dont::remove_reference_t<ArrayTs>>...>>{},
    _forward<ArrayTs>(arrays)...);
}

}  // namespace dont::array