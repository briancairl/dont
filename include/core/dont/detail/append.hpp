// clang-format off
#pragma once

// Dont
#include "dont/common.hpp"

namespace dont::detail
{

template <template <typename, typename> class Condition, typename PackLikeT, typename AppendT> struct AppendIf;

template <
  template <typename, typename> class Condition,
  template <typename...> class PackLike,
  typename... Ts,
  typename AppendT>
struct AppendIf<Condition, PackLike<Ts...>, AppendT>
{
  using type = if_else_t<
    Condition<AppendT, PackLike<Ts...>>::value,
    PackLike<Ts..., AppendT>,
    PackLike<Ts...>
  >;
};

}  // namespace dont::detail
// clang-format on