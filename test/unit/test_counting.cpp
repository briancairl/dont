/**
 * @copyright 2024-present Brian Cairl
 *
 * @file test_counting.cpp
 */

// GTest
#include <gtest/gtest.h>

// Dont
#include "dont/counting.hpp"

using namespace dont;

template <typename T> void print() {
  std::cerr << __PRETTY_FUNCTION__ << std::endl;
}

TEST(MakeIntegerSequence, Empty) {
  using Result = typename MakeIntegerSequence<int, 0>::type;
  print<Result>();
  EXPECT_EQ(Result::size(), 0);
}

TEST(MakeIntegerSequence, NonEmpty) {
  using Result = typename MakeIntegerSequence<int, 10>::type;
  print<Result>();
  EXPECT_EQ(Result::size(), 10);
}

TEST(MakeIntegerSequence, NonEmptyStartOffset) {
  using Result = typename MakeIntegerSequence<int, 10, 5>::type;
  print<Result>();
  EXPECT_EQ(Result::size(), 5);
}
