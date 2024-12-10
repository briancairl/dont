/**
 * @copyright 2024-present Brian Cairl
 *
 * @file test_append.cpp
 */

// GTest
#include <gtest/gtest.h>

// Dont
#include "dont/append.hpp"
#include "dont/common.hpp"
#include "dont/conditions.hpp"

using namespace dont;

TEST(AppendIf, AddToEmptyPack)
{
  using Input = Pack<>;
  EXPECT_EQ(Input::size(), 0UL);

  using Result1 = append_t<Input, float>;
  EXPECT_EQ(Result1::size(), 1UL);

  using Result2 = append_t<Result1, float>;
  EXPECT_EQ(Result2::size(), 2UL);
}

TEST(AppendIf, AddToEmptyPackAccepted)
{
  using Input = Pack<>;
  EXPECT_EQ(Input::size(), 0UL);

  using Result = append_if_t<Identity, Input, float>;
  EXPECT_EQ(Result::size(), 1UL);
}

TEST(AppendIf, AddToEmptyPackRejected)
{
  using Input = Pack<>;
  EXPECT_EQ(Input::size(), 0UL);

  using Result = append_if_t<IsMember, Input, float>;
  EXPECT_EQ(Result::size(), 0UL);
}

TEST(AppendIf, SetAdd)
{
  using Input = Pack<>;
  EXPECT_EQ(Input::size(), 0UL);

  using Result1 = set_add_t<Input, float>;
  EXPECT_EQ(Result1::size(), 1UL);

  using Result2 = set_add_t<Result1, float>;
  EXPECT_EQ(Result2::size(), 1UL);
}
