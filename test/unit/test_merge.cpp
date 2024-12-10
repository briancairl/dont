/**
 * @copyright 2024-present Brian Cairl
 *
 * @file test_merge.cpp
 */

// GTest
#include <gtest/gtest.h>

// Dont
#include "dont/common.hpp"
#include "dont/conditions.hpp"
#include "dont/merge.hpp"

using namespace dont;

TEST(MergeIf, EmptyPacks) {
  using Input = Pack<>;
  EXPECT_EQ(Input::size(), 0UL);

  using Result = merge_t<Input, Input>;
  EXPECT_EQ(Result::size(), 0UL);
}

TEST(MergeIf, AddToEmptyPackAccepted) {
  using InputLHS = Pack<>;
  EXPECT_EQ(InputLHS::size(), 0UL);

  using InputRHS = Pack<float>;
  EXPECT_EQ(InputRHS::size(), 1UL);

  using Result = merge_if_t<Identity, InputLHS, InputRHS>;
  EXPECT_EQ(Result::size(), 1UL);
}

TEST(MergeIf, SetUnionOthogonal) {
  using InputLHS = Pack<int>;
  EXPECT_EQ(InputLHS::size(), 1UL);

  using InputRHS = Pack<float>;
  EXPECT_EQ(InputRHS::size(), 1UL);

  using Result = set_union_t<InputLHS, InputRHS>;
  EXPECT_EQ(Result::size(), 2UL);
}

TEST(MergeIf, SetUnionNonOthogonal) {
  using InputLHS = Pack<int>;
  EXPECT_EQ(InputLHS::size(), 1UL);

  using InputRHS = Pack<int>;
  EXPECT_EQ(InputRHS::size(), 1UL);

  using Result = set_union_t<InputLHS, InputRHS>;
  EXPECT_EQ(Result::size(), 1UL);
}
