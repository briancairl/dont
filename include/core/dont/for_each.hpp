#pragma once

// Dont
#include "dont/common.hpp"
#include "dont/detail/for_each.hpp"

namespace dont
{

/**
 * @brief "Iterates" over <code>packs...</code> simultaneously which support access by static index
 */
template <template <size_t> class RuntimeAccessByIndex, typename UnaryCallableT, typename... PackLikeTs>
auto for_each(UnaryCallableT&& callable, PackLikeTs&&... packs)
{
  return detail::for_each<RuntimeAccessByIndex>(
    _forward<UnaryCallableT>(callable),
    make_index_sequence_t<pack_size_v<PackLikeTs...>>{},
    _forward<PackLikeTs>(packs)...);
}

}  // namespace dont