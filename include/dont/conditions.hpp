#pragma once

#include "dont/common.hpp"

namespace dont
{

template <typename QueryT, typename PackLikeT> struct Identity : True
{};

template <typename QueryT, typename PackLikeT> struct IsMember : False
{};

template <typename QueryT, template <typename...> class Pack, typename... Ts>
struct IsMember<QueryT, Pack<Ts...>> : Constant<bool, (is_same_v<QueryT, Ts> or ...)>
{};

template <template <typename, typename> class Condition> struct Invert
{
  template <typename QueryT, typename PackLikeT> struct eval : Constant<bool, !Condition<QueryT, PackLikeT>::value>
  {};
};

template <typename... TargetTs> struct Is
{
  static_assert(sizeof...(TargetTs) > 0, "'TargetTs' may not be empty");
  template <typename QueryT, typename _> struct eval : Constant<bool, (is_same_v<TargetTs, QueryT> or ...)>
  {};
};

}  // namespace dont