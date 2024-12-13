#pragma once

// Dont
#include "dont/conditions.hpp"
#include "dont/detail/append.hpp"

namespace dont
{

/**
 * @brief Holds a type key/value pair
 */
template <typename KeyT, typename ValueT> struct KeyValue
{
  using type = ValueT;
};

/**
 * @brief Checks if <code>T</code> is a valid intance of <code>KeyValue</code>
 */
template <typename T> struct IsKeyValue : False
{};

/**
 * @copydoc IsKeyValue
 */
template <typename KeyT, typename ValueT> struct IsKeyValue<KeyValue<KeyT, ValueT>> : True
{};

/**
 * @copydoc IsKeyValue
 */
template <typename T> constexpr bool is_key_value_v = IsKeyValue<T>::value;

/**
 * @brief Holds a type key, constant value pair
 */
template <typename KeyT, typename ValueT, ValueT kValue> struct KeyConst : Constant<ValueT, kValue>
{};

/**
 * @brief Checks if <code>T</code> is a valid intance of <code>KeyConst</code>
 */
template <typename T> struct IsKeyConst : False
{};

/**
 * @copydoc IsKeyConst
 */
template <typename KeyT, typename ConstantT, ConstantT kValue>
struct IsKeyConst<KeyConst<KeyT, ConstantT, kValue>> : True
{};

/**
 * @copydoc IsKeyConst
 */
template <typename T> constexpr bool is_key_constant_v = IsKeyConst<T>::value;

/**
 * @brief Extracts key type from <code>KeyValue</code> or <code>KeyConst</code>
 */
template <typename KeyValueT> struct Key;

/**
 * @copydoc Key
 */
template <typename KeyT, typename ValueT> struct Key<KeyValue<KeyT, ValueT>>
{
  using type = KeyT;
};

/**
 * @copydoc Key
 */
template <typename KeyT, typename ValueT, ValueT kValue> struct Key<KeyConst<KeyT, ValueT, kValue>>
{
  using type = KeyT;
};

/**
 * @copydoc Key
 */
template <typename KeyValueT> using key_t = typename Key<KeyValueT>::type;

/**
 * @brief Holds a mapping of type keys to other types / constants
 */
template <typename... KeyValueTs> struct Map
{
  static_assert(((is_key_value_v<KeyValueTs> || is_key_constant_v<KeyValueTs>)&&...), "'KeyValueTs' are not all valid");
  static constexpr auto size() { return sizeof...(KeyValueTs); }
};

/**
 * @brief Checks if <code>T</code> is a valid intance of <code>Map</code>
 */
template <typename T> struct IsMap : False
{};

/**
 * @copydoc IsMap
 */
template <typename... KeyValueTs> struct IsMap<Map<KeyValueTs...>> : True
{};

/**
 * @copydoc IsMap
 */
template <typename T> constexpr bool is_map_v = IsMap<T>::value;

/**
 * @brief Checks if <code>KeyT</code> is key type in <code>MapT = Map<...KVs...></code>
 */
template <typename MapT, typename KeyT> struct MapContains;

/**
 * @copydoc typename
 */
template <typename... KeyValueTs, typename QueryKeyT>
struct MapContains<Map<KeyValueTs...>, QueryKeyT> : Constant<bool, (is_same_v<key_t<KeyValueTs>, QueryKeyT> || ...)>
{};

/**
 * @copydoc typename
 */
template <typename MapT, typename KeyT> constexpr bool map_contains_v = MapContains<MapT, KeyT>::value;

/**
 * @brief Finds a value type/constant associated with <code>KeyT</code> in <code>MapT = Map<...KVs...></code>
 */
template <typename MapT, typename KeyT> struct MapLookup;

/**
 * @copydoc MapLookup
 */
template <typename KeyT, typename MatchValueT, typename... OtherKeyValueTs>
struct MapLookup<Map<KeyValue<KeyT, MatchValueT>, OtherKeyValueTs...>, KeyT>
{
  using type = MatchValueT;
};

/**
 * @copydoc MapLookup
 */
template <typename KeyT, typename CandidateKeyT, typename CandidateValueT, typename... OtherKeyValueTs>
struct MapLookup<Map<KeyValue<CandidateKeyT, CandidateValueT>, OtherKeyValueTs...>, KeyT>
    : MapLookup<Map<OtherKeyValueTs...>, KeyT>
{};

/**
 * @copydoc MapLookup
 */
template <typename KeyT, typename MatchValueT, MatchValueT kMatchValue, typename... OtherKeyValueTs>
struct MapLookup<Map<KeyConst<KeyT, MatchValueT, kMatchValue>, OtherKeyValueTs...>, KeyT>
{
  static constexpr MatchValueT value = kMatchValue;
};

/**
 * @copydoc MapLookup
 */
template <
  typename KeyT,
  typename CandidateKeyT,
  typename CandidateValueT,
  CandidateValueT kCandidateValue,
  typename... OtherKeyValueTs>
struct MapLookup<Map<KeyConst<CandidateKeyT, CandidateValueT, kCandidateValue>, OtherKeyValueTs...>, KeyT>
    : MapLookup<Map<OtherKeyValueTs...>, KeyT>
{};

/**
 * @copydoc MapLookup
 * @note type lookup
 */
template <typename MapT, typename KeyT> using map_lookup_t = typename MapLookup<MapT, KeyT>::type;

/**
 * @copydoc MapLookup
 * @note constant value lookup
 */
template <typename MapT, typename KeyT> constexpr auto map_lookup_v = MapLookup<MapT, KeyT>::value;

}  // namespace dont