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
    using ReturnType = decltype(callable(SliceElementAccess{}(_forward<PackLikeTs>(packs))...));
    static_assert(is_same_v<ReturnType, void> or is_same_v<ReturnType, bool>);
    if constexpr (is_same_v<ReturnType, void>)
    {
      callable(SliceElementAccess{}(_forward<PackLikeTs>(packs))...);
      return true;
    }
    else
    {
      return callable(SliceElementAccess{}(_forward<PackLikeTs>(packs))...);
    }
  }
};

template <template <size_t> class RuntimeAccessByIndex, typename UnaryCallableT, size_t... Is, typename... PackLikeTs>
auto for_each(UnaryCallableT&& callable, [[maybe_unused]] index_sequence_t<Is...> _, PackLikeTs&&... packs)
{
  return (
    SliceAdapter<RuntimeAccessByIndex<Is>>::template slice(
      _forward<UnaryCallableT>(callable), _forward<PackLikeTs>(packs)...) and
    ...);
}

}  // namespace dont::detail
// clang-format on