#pragma once

#include "dont/common.hpp"
#include "dont/conditions.hpp"

namespace dont
{
namespace detail
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

}  // namespace detail

template <template <typename, typename> class Condition, typename InputPackLikeT>
struct RemoveIf : detail::RemoveIf<Condition, InputPackLikeT, make_empty_t<InputPackLikeT>>
{};

template <template <typename, typename> class Condition, typename InputPackLikeT>
using remove_if_t = typename RemoveIf<Condition, InputPackLikeT>::type;

}  // namespace dont