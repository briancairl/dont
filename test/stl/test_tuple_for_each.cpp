/**
 * @copyright 2024-present Brian Cairl
 *
 * @file test_tuple_for_each.cpp
 */

// GTest
#include <gtest/gtest.h>

// Dont
#include "dont/stl/tuple/for_each.hpp"

using namespace dont;

TEST(TupleForEach, IterateOneTuple)
{
  size_t count = 0;

  tuple::for_each([&count](const auto& element) { ++count; }, std::make_tuple(0, 0.1, 2.0F));

  EXPECT_EQ(count, static_cast<size_t>(3));
}

TEST(TupleForEach, IterateTwoTuples)
{
  size_t count = 0;

  tuple::for_each(
    [&count](const auto element1, const auto element2) {
      EXPECT_EQ(element1, element2);
      ++count;
    },
    std::make_tuple(0, 0.1, 2.0F),
    std::make_tuple(0, 0.1, 2.0F));

  EXPECT_EQ(count, static_cast<size_t>(3));
}

TEST(TupleForEach, IterateReversed)
{
  size_t count = 0;

  tuple::for_each(
    [&count](auto& element) {
      std::cout << '[' << count << "] " << element << std::endl;
      ++count;
    },
    tuple::reversed(std::make_tuple(0, 0.1, 2.0F)));

  EXPECT_EQ(count, static_cast<size_t>(3));
}
