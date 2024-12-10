#pragma once

#include "dont/common.hpp"

namespace dont
{

/**
 * @brief Always evaluates to <code>true</code>
 */
template <typename QueryT, typename PackLikeT> struct Identity : True
{};

/**
 * @brief Evaluates to <code>true</code> if <code>PackLikeT</code> does contains <code>QueryT</code>
 */
template <typename QueryT, typename PackLikeT> struct IsMember : False
{};

/**
 * @copydoc IsMember
 */
template <typename QueryT, template <typename...> class Pack, typename... Ts>
struct IsMember<QueryT, Pack<Ts...>> : Constant<bool, (is_same_v<QueryT, Ts> or ...)>
{};

/**
 * @brief Inverts the result of <code>Condition</code> (boolean NOT)
 */
template <template <typename, typename> class Condition> struct Invert
{
  template <typename QueryT, typename PackLikeT> struct eval : Constant<bool, !Condition<QueryT, PackLikeT>::value>
  {};
};

/**
 * @brief Evaluates to <code>true</code> if <code>QueryT</code> is one of <code>TargetTs...</code>
 */
template <typename... TargetTs> struct Is
{
  static_assert(sizeof...(TargetTs) > 0, "'TargetTs' may not be empty");
  template <typename QueryT, typename _> struct eval : Constant<bool, (is_same_v<TargetTs, QueryT> or ...)>
  {};
};

}  // namespace dont