/**
 * @copyright 2024-present Brian Cairl
 *
 * @file test_map.cpp
 */

// GTest
#include <gtest/gtest.h>

// Dont
#include "dont/common.hpp"
#include "dont/map.hpp"

using namespace dont;

TEST(Map, Empty)
{
  using M = Map<>;
  EXPECT_EQ(M::size(), 0UL);
  EXPECT_FALSE((map_contains_v<M, int>));
  EXPECT_FALSE((map_contains_v<M, float>));
}

TEST(Map, FindType)
{
  using M = Map<KeyValue<int, float>, KeyValue<float, int>, KeyConst<char, int, 1>>;
  EXPECT_EQ(M::size(), 3UL);
  EXPECT_TRUE((is_same_v<map_lookup_t<M, int>, float>));
  EXPECT_TRUE((is_same_v<map_lookup_t<M, float>, int>));
  EXPECT_EQ((map_lookup_v<M, char>), 1);
}
