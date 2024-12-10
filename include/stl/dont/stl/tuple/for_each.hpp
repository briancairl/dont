#pragma once

// C++ Standard Library
#include <tuple>

// Dont
#include "dont/stl/tuple/detail/for_each.hpp"


namespace dont::tuple
{

/**
 * @brief "Iterates" over the elements of <code>tups...</code> (of equal length) simultaneously
 */
template <typename UnaryCallableT, typename... TupleTs> auto for_each(UnaryCallableT&& callable, TupleTs&&... tups)
{
  return ::dont::for_each<detail::TupleElementAccess>(_forward<UnaryCallableT>(callable), _forward<TupleTs>(tups)...);
}

}  // namespace dont::tuple