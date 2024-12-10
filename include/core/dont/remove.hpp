#pragma once

// Dont
#include "dont/detail/remove.hpp"

namespace dont
{

/**
 * @brief Removes types from a template parameter <code>PackLikeT</code> which meet some <code>Condition</code>
 */
template <template <typename, typename> class Condition, typename PackLikeT>
struct RemoveIf : detail::RemoveIf<Condition, PackLikeT, make_empty_t<PackLikeT>>
{};

/**
 * @copydoc RemoveIf
 */
template <template <typename, typename> class Condition, typename PackLikeT>
using remove_if_t = typename RemoveIf<Condition, PackLikeT>::type;

}  // namespace dont