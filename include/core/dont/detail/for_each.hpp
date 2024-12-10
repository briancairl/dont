// clang-format off
#pragma once

// Dont
#include "dont/common.hpp"
#include "dont/counting.hpp"

namespace dont::detail
{

template <typename SliceElementAccess> struct SliceAdapter
{
  template <typename UnaryCallableT, typename... PackLikeTs>
  static auto slice(UnaryCallableT callable, PackLikeTs&&... packs)
  {
    callable(SliceElementAccess{}(_forward<PackLikeTs>(packs))...);
    return 1;
  }
};

template <template <size_t> class RuntimeAccessByIndex, typename UnaryCallableT, size_t... Is, typename... PackLikeTs>
auto for_each(UnaryCallableT&& callable, [[maybe_unused]] index_sequence_t<Is...> _, PackLikeTs&&... packs)
{
  return (
    SliceAdapter<RuntimeAccessByIndex<Is>>::template slice(
      _forward<UnaryCallableT>(callable), _forward<PackLikeTs>(packs)...) +
    ...);
}

}  // namespace dont::detail
// clang-format on