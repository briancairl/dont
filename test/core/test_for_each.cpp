/**
 * @copyright 2024-present Brian Cairl
 *
 * @file test_for_each.cpp
 */

// GTest
#include <gtest/gtest.h>

// Dont
#include "dont/common.hpp"
#include "dont/for_each.hpp"

using namespace dont;

template <size_t I> struct Access
{
  template <typename T> size_t operator()(const T& v) const { return I; }
};

TEST(ForEach, IterateOnePack)
{
  size_t count = 0;

  for_each<Access>(
    [&count](size_t element) {
      EXPECT_GE(element, static_cast<size_t>(0));
      EXPECT_LT(element, static_cast<size_t>(3));
      ++count;
    },
    Pack<int, float, char>{});

  EXPECT_EQ(count, static_cast<size_t>(3));
}

TEST(ForEach, IterateTwoPacks)
{
  size_t count = 0;

  for_each<Access>(
    [&count](size_t element1, size_t element2) {
      EXPECT_GE(element1, static_cast<size_t>(0));
      EXPECT_LT(element1, static_cast<size_t>(3));

      EXPECT_GE(element2, static_cast<size_t>(0));
      EXPECT_LT(element2, static_cast<size_t>(3));
      ++count;
    },
    Pack<int, float, char>{},
    Pack<char, float, int>{});

  EXPECT_EQ(count, static_cast<size_t>(3));
}

TEST(ForEach, EarlyStop)
{
  size_t count = 0;

  for_each<Access>(
    [&count](size_t element) {
      EXPECT_GE(element, static_cast<size_t>(0));
      EXPECT_LT(element, static_cast<size_t>(3));
      ++count;
      if (count == 1)
      {
        return false;
      }
      return true;
    },
    Pack<int, float, char>{});

  EXPECT_EQ(count, static_cast<size_t>(1));
}