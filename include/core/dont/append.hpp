#pragma once

// Dont
#include "dont/conditions.hpp"
#include "dont/detail/append.hpp"

namespace dont
{

/**
 * @brief Appends type, <code>AppendT</code> to pack <code>PackLikeT</code> if <code>Condition</code> is met
 */
template <template <typename, typename> class Condition, typename PackLikeT, typename AppendT>
struct AppendIf : detail::AppendIf<Condition, PackLikeT, AppendT>
{};

/**
 * @copydoc AppendIf
 */
template <template <typename, typename> class Condition, typename PackLikeT, typename AppendT>
using append_if_t = typename AppendIf<Condition, PackLikeT, AppendT>::type;

/**
 * @brief Appends type, <code>AppendT</code> to pack <code>PackLikeT</code>
 */
template <typename PackLikeT, typename AppendT> using append_t = typename AppendIf<Identity, PackLikeT, AppendT>::type;

/**
 * @brief Appends type, <code>AppendT</code> to pack <code>PackLikeT</code> if is not already included in the pack
 * (treated as a set)
 */
template <typename PackLikeT, typename AppendT>
using set_add_t = typename AppendIf<Invert<IsMember>::eval, PackLikeT, AppendT>::type;

}  // namespace dont