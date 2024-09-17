/**
 * @file
 * @brief  Unit tests for caching algorithms
 * @author Victor Baldin
 */
#include <cstddef>
#include <vector>

#include <gtest/gtest.h>

#include "common.hh"
#include "lfu_cache.hh"

namespace {

std::size_t getLfuHits(std::size_t cache_sz, std::vector<int> keys) {
  caches::LfuCache<int, int> cache{cache_sz};
  std::size_t hits = 0;

  for (std::size_t i = 0; i < keys.size(); ++i) {
    if (cache.get(keys[i], common::slowGetPage).second) {
      ++hits;
    }
  }
  return hits;
}

}  // namespace

TEST(cache_hits, lfu) {
  EXPECT_EQ(getLfuHits(1,                             {1}), 0);
  EXPECT_EQ(getLfuHits(2,              {1, 2, 1, 2, 1, 2}), 4);
  EXPECT_EQ(getLfuHits(3,  {1, 2, 3, 1, 2, 3, 1, 2, 4, 4}), 6);
  EXPECT_EQ(getLfuHits(5, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}), 0);
}

TEST(cache_hits, belady) {

}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
