#pragma once

// Dont
#include "dont/common.hpp"
#include "dont/conditions.hpp"
#include "dont/detail/merge.hpp"

namespace dont
{

/**
 * @brief Merges types of several template parameter <code>Packs...</code> based on <code>Condition</code>
 */
template <template <typename, typename> class Condition, typename... Packs>
struct MergeIf : detail::MergeIf<Condition, Packs...>
{};

/**
 * @copydoc MergeIf
 */
template <template <typename, typename> class Condition, typename... Packs>
using merge_if_t = typename MergeIf<Condition, Packs...>::type;

/**
 * @brief Merges types of several template parameter <code>Packs...</code>
 */
template <typename... Packs> using merge_t = typename MergeIf<Identity, Packs...>::type;

/**
 * @brief Merges types of several template parameter <code>Packs...</code> to form a pack containing only unique types
 */
template <typename... Packs> using set_union_t = typename MergeIf<Invert<IsMember>::eval, Packs...>::type;

}  // namespace dont