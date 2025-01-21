#pragma once

// Dont
#include "dont/common.hpp"

namespace dont
{

/**
 * @brief Creates a type, SrcPackLike<Ts...> from SrcPackLikeT by packing in DstPackLike
 */
template <template <typename...> class DstPackLike, typename SrcPackLikeT> struct Imbue;

template <template <typename...> class DstPackLike, template <typename...> class SrcPackLike, typename... Ts>
struct Imbue<DstPackLike, SrcPackLike<Ts...>>
{
  using type = DstPackLike<Ts...>;
};

/**
 * @copydoc Imbue
 */
template <template <typename...> class DstPackLike, typename SrcPackLikeT>
using imbue_t = typename Imbue<DstPackLike, SrcPackLikeT>::type;

}  // namespace dont
