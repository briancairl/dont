// clang-format off
#pragma once

// Dont
#include "dont/common.hpp"

namespace dont::detail
{

template <template <typename, typename> class Condition, typename InputPackLikeT, typename ResultPackLikeT>
struct RemoveIf;

template <
  template <typename, typename>
  class Condition,
  template <typename...>
  class InputPackLike,
  typename ResultPackLikeT>
struct RemoveIf<Condition, InputPackLike<>, ResultPackLikeT>
{
  using type = ResultPackLikeT;
};

template <
  template <typename, typename>
  class Condition,
  template <typename...>
  class PackLike,
  typename RemoveCandidateT,
  typename... RemainingTs,
  typename... RetainedTs>
struct RemoveIf<Condition, PackLike<RemoveCandidateT, RemainingTs...>, PackLike<RetainedTs...>>
    : if_else_t<
        Condition<RemoveCandidateT, PackLike<RemoveCandidateT, RemainingTs...>>::value,
        RemoveIf<Condition, PackLike<RemainingTs...>, PackLike<RetainedTs...>>,
        RemoveIf<Condition, PackLike<RemainingTs...>, PackLike<RetainedTs..., RemoveCandidateT>>>
{};

}  // namespace dont::detail
// clang-format on