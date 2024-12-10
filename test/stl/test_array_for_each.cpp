/**
 * @copyright 2024-present Brian Cairl
 *
 * @file test_array_for_each.cpp
 */

// GTest
#include <gtest/gtest.h>

// Dont
#include "dont/stl/array/for_each.hpp"

using namespace dont;

TEST(ArrayForEach, IterateOneArray)
{
  size_t count = 0;

  int sum = 0;

  const std::array<int, 3> arr = { 1, 2, 3 };

  array::for_each(
    [&count, &sum](const auto& element) {
      ++count;
      sum += element;
    },
    arr);

  EXPECT_EQ(count, static_cast<size_t>(3));
  EXPECT_EQ(sum, 6);
}

TEST(ArrayForEach, IterateTwoArrays)
{
  size_t count = 0;

  int sum = 0;

  const std::array<int, 3> arr = { 1, 2, 3 };

  array::for_each(
    [&count, &sum](const auto element1, const auto element2) {
      EXPECT_EQ(element1, element2);
      ++count;
      sum += element1;
      sum += element2;
    },
    arr,
    arr);

  EXPECT_EQ(count, static_cast<size_t>(3));
  EXPECT_EQ(sum, 12);
}

TEST(ArrayForEach, IterateOneCArray)
{
  size_t count = 0;

  int sum = 0;

  const int arr[3] = { 1, 2, 3 };

  array::for_each(
    [&count, &sum](const auto& element) {
      ++count;
      sum += element;
    },
    arr);

  EXPECT_EQ(count, static_cast<size_t>(3));
  EXPECT_EQ(sum, 6);
}

TEST(ArrayForEach, IterateTwoCArrays)
{
  size_t count = 0;

  int sum = 0;

  const int arr[3] = { 1, 2, 3 };

  array::for_each(
    [&count, &sum](const auto element1, const auto element2) {
      EXPECT_EQ(element1, element2);
      ++count;
      sum += element1;
      sum += element2;
    },
    arr,
    arr);

  EXPECT_EQ(count, static_cast<size_t>(3));
  EXPECT_EQ(sum, 12);
}

TEST(ArrayForEach, IterateMixedArrays)
{
  size_t count = 0;

  int sum = 0;

  const std::array<int, 3> arr1 = { 1, 2, 3 };
  const int arr2[3] = { 1, 2, 3 };

  array::for_each(
    [&count, &sum](const auto element1, const auto element2) {
      EXPECT_EQ(element1, element2);
      ++count;
      sum += element1;
      sum += element2;
    },
    arr1,
    arr2);

  EXPECT_EQ(count, static_cast<size_t>(3));
  EXPECT_EQ(sum, 12);
}
