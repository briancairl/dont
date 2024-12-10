#pragma once

namespace dont
{

template <typename T, T Value> struct Constant
{
  static constexpr T value = Value;
  constexpr operator T() const { return Value; }
};

struct True : Constant<bool, true>
{};

struct False : Constant<bool, false>
{};

template <typename L, typename R> struct IsSame : False
{};

template <typename T> struct IsSame<T, T> : True
{};

template <typename L, typename R> constexpr bool is_same_v = IsSame<L, R>::value;

template <bool U, typename F, typename S> struct IfElse;

template <typename F, typename S> struct IfElse<true, F, S>
{
  using type = F;
};

template <typename F, typename S> struct IfElse<false, F, S>
{
  using type = S;
};

template <bool U, typename F, typename S> using if_else_t = typename IfElse<U, F, S>::type;

template <typename... Ts> struct Pack
{
  static constexpr auto size() { return sizeof...(Ts); }
};

using size_t = decltype(Pack<>::size());

template <typename T> struct RemoveReference
{
  using type = T;
};

template <typename T> struct RemoveReference<T&>
{
  using type = T;
};

template <typename T> struct RemoveReference<T&&>
{
  using type = T;
};

template <typename T> using remove_reference_t = typename RemoveReference<T>::type;

template <typename T> constexpr T&& forward(remove_reference_t<T>& v) { return static_cast<T&&>(v); }

template <typename T> constexpr T&& forward(remove_reference_t<T>&& v) { return static_cast<T&&>(v); }

/**
 * @brief Creates a type with an empty param pack
 */
template <typename PackLikeT> struct MakeEmpty;

template <typename PackLikeT> using make_empty_t = typename MakeEmpty<PackLikeT>::type;

/**
 * @brief Creates a type with an empty param pack
 */
template <template <typename...> class PackLike, typename... Ts> struct MakeEmpty<PackLike<Ts...>>
{
  using type = PackLike<>;
};


/**
 * @brief Computes size of a pack
 */
template <typename... PackLikeTs> struct PackSize;

/**
 * @copydoc PackSize
 */
template <template <typename...> class PackLike, typename... Ts>
struct PackSize<PackLike<Ts...>> : Constant<size_t, sizeof...(Ts)>
{};

/**
 * @copydoc PackSize
 * @note common size resolution
 */
template <typename FirstPackT, typename SecondPackT, typename... OtherPackTs>
struct PackSize<FirstPackT, SecondPackT, OtherPackTs...> : PackSize<FirstPackT>
{
  static_assert(PackSize<FirstPackT>() == PackSize<SecondPackT, OtherPackTs...>(), "pack sizes do not match");
};

template <typename... PackLikeTs> constexpr auto pack_size_v = PackSize<PackLikeTs...>::value;

}  // namespace dont