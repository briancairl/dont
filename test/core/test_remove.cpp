/**
 * @copyright 2024-present Brian Cairl
 *
 * @file test_remove.cpp
 */

// GTest
#include <gtest/gtest.h>

// Dont
#include "dont/common.hpp"
#include "dont/conditions.hpp"
#include "dont/remove.hpp"

using namespace dont;

TEST(RemoveIf, FilterType)
{
  using Input = Pack<int, float, int, float>;
  EXPECT_EQ(Input::size(), 4UL);

  using Result = remove_if_t<Is<int>::eval, Input>;
  EXPECT_EQ(Result::size(), 2UL);
}


TEST(RemoveIf, FilterNone)
{
  using Input = Pack<int, float, int, float>;
  EXPECT_EQ(Input::size(), 4UL);

  using Result = remove_if_t<Is<char>::eval, Input>;
  EXPECT_EQ(Result::size(), 4UL);
}


TEST(RemoveIf, FilterEmpty)
{
  using Input = Pack<>;
  EXPECT_EQ(Input::size(), 0UL);

  using Result = remove_if_t<Is<char>::eval, Input>;
  EXPECT_EQ(Result::size(), 0UL);
}
