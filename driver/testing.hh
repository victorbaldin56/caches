#ifndef PROBLEM_LC_TESTING_HH_
#define PROBLEM_LC_TESTING_HH_

#include <cstddef>

#include <gtest/gtest.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

namespace caches {

namespace testing {

struct Test {
  std::size_t cache_sz_;
  std::size_t elem_count_;
  std::vector<int> keys_;

  std::size_t hit_count_;
};

// clang-format off
static const Test g_lfuTests[] = {
  {1,  1,                             {1}, 0},
  {2,  6,             {1, 2, 1, 2, 1,  2}, 4},
  {3, 10, {1, 2, 3, 1, 2, 3, 1, 2, 4,  4}, 6},
  {5, 10, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 0},
};
// clang-format on

}  // namespace testing

}  // namespace caches

#endif
