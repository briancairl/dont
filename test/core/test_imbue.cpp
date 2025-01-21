/**
 * @copyright 2025-present Brian Cairl
 *
 * @file test_imbue.cpp
 */

// GTest
#include <gtest/gtest.h>

// Dont
#include "dont/imbue.hpp"

using namespace dont;

template <typename... Ts> struct TestPack : Pack<Ts...>
{};

TEST(Imbue, Sanity)
{
  using Input = Pack<int, float, char>;
  EXPECT_EQ(Input::size(), 3UL);

  using Output = imbue_t<TestPack, Input>;
  EXPECT_EQ(Output::size(), 3UL);
}
