#pragma once

namespace dont
{

/**
 * @brief Represents a constant value of type <code>T</code>
 */
template <typename T, T Value> struct Constant
{
  static constexpr T value = Value;
  constexpr operator T() const { return Value; }
};

/**
 * @brief Represents a constant value <code>true</code>
 */
struct True : Constant<bool, true>
{};

/**
 * @brief Represents a constant value <code>fase</code>
 */
struct False : Constant<bool, false>
{};

/**
 * @brief Evaluates to <code>true</code> if <code>L</code> and <code>R</code> are the same type
 */
template <typename L, typename R> struct IsSame : False
{};

/**
 * @copydoc IsSame
 * @note true case
 */
template <typename T> struct IsSame<T, T> : True
{};

/**
 * @copydoc IsSame
 */
template <typename L, typename R> constexpr bool is_same_v = IsSame<L, R>::value;

/**
 * @brief Evaluates to type <code>F</code> if <code>U == ture</code>, otherwise <code>S</code>
 */
template <bool U, typename F, typename S> struct IfElse;

/**
 * @copydoc IfElse
 * @note true case
 */
template <typename F, typename S> struct IfElse<true, F, S>
{
  using type = F;
};

/**
 * @copydoc IfElse
 * @note false case
 */
template <typename F, typename S> struct IfElse<false, F, S>
{
  using type = S;
};

/**
 * @copydoc IfElse
 */
template <bool U, typename F, typename S> using if_else_t = typename IfElse<U, F, S>::type;

/**
 * @brief Basic parameter pack utility type
 */
template <typename... Ts> struct Pack
{
  static constexpr auto size() { return sizeof...(Ts); }
};

/**
 * @brief Standard unsigned long int type
 */
using size_t = decltype(Pack<>::size());

/**
 * @brief Evaluates to type <code>T</code> with reference qualifier removed
 */
template <typename T> struct RemoveReference
{
  using type = T;
};

/**
 * @copydoc RemoveReference
 */
template <typename T> struct RemoveReference<T&>
{
  using type = T;
};

/**
 * @copydoc RemoveReference
 */
template <typename T> struct RemoveReference<T&&>
{
  using type = T;
};

/**
 * @copydoc RemoveReference
 */
template <typename T> using remove_reference_t = typename RemoveReference<T>::type;

/**
 * @brief Evaluates to type <code>T</code> with <code>const</code> qualifier removed
 */
template <typename T> struct RemoveConst
{
  using type = T;
};

/**
 * @copydoc RemoveConst
 */
template <typename T> struct RemoveConst<const T>
{
  using type = T;
};

/**
 * @copydoc RemoveConst
 */
template <typename T> using remove_const_t = typename RemoveConst<T>::type;

/**
 * @brief Creates a forwarding reference <code>T&&</code>
 */
template <typename T> constexpr T&& _forward(remove_reference_t<T>& v) { return static_cast<T&&>(v); }

/**
 * @copydoc _forward
 */
template <typename T> constexpr T&& _forward(remove_reference_t<T>&& v) { return static_cast<T&&>(v); }

/**
 * @brief Creates a type with an empty param pack
 */
template <typename PackLikeT> struct MakeEmpty;

/**
 * @copydoc MakeEmpty
 */
template <typename PackLikeT> using make_empty_t = typename MakeEmpty<PackLikeT>::type;

/**
 * @copydoc MakeEmpty
 */
template <template <typename...> class PackLike, typename... Ts> struct MakeEmpty<PackLike<Ts...>>
{
  using type = PackLike<>;
};

/**
 * @brief Computes size of several template parameter packs
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

/**
 * @copydoc PackSize
 */
template <typename... PackLikeTs> constexpr auto pack_size_v = PackSize<PackLikeTs...>::value;

}  // namespace dont