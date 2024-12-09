#pragma once

#include "dont/append.hpp"
#include "dont/common.hpp"
#include "dont/conditions.hpp"

namespace dont {

template <template <typename, typename> class Condition, typename... Packs>
struct MergeIf;

template <template <typename, typename> class Condition, typename... Packs>
using merge_if_t = typename MergeIf<Condition, Packs...>::type;

template <template <typename, typename> class Condition,
          template <typename...> class PackLike, typename... Ts>
struct MergeIf<Condition, PackLike<Ts...>> {
  using type = PackLike<Ts...>;
};

template <template <typename, typename> class Condition, typename Mismatch1,
          typename Mismatch2>
struct MergeIf<Condition, Mismatch1, Mismatch2> {
  static_assert(is_same_v<Mismatch1, Mismatch2>,
                "Merged packs must have the same template: MergeIf< "
                "[Condition], PackLike<Pack1Ts...>, PackLike<Pack2Ts...>>");
};

template <template <typename, typename> class Condition,
          template <typename...> class PackLike, typename... Ts>
struct MergeIf<Condition, PackLike<Ts...>, PackLike<>> {
  using type = PackLike<Ts...>;
};

template <template <typename, typename> class Condition,
          template <typename...> class PackLike, typename... T1s, typename FT2,
          typename... OtherT2s>
struct MergeIf<Condition, PackLike<T1s...>, PackLike<FT2, OtherT2s...>> {
  using type =
      typename MergeIf<Condition, append_if_t<Condition, PackLike<T1s...>, FT2>,
                       PackLike<OtherT2s...>>::type;
};

template <template <typename, typename> class Condition, typename Pack1T,
          typename Pack2T, typename Pack3T, typename... OtherPackTs>
struct MergeIf<Condition, Pack1T, Pack2T, Pack3T, OtherPackTs...> {
  using type =
      typename MergeIf<Condition, merge_if_t<Condition, Pack1T, Pack2T>, Pack3T,
                       OtherPackTs...>::type;
};

template <typename... Packs>
using merge_t = typename MergeIf<Identity, Packs...>::type;

template <typename... Packs>
using set_union_t = typename MergeIf<Invert<IsMember>::eval, Packs...>::type;

} // namespace dont