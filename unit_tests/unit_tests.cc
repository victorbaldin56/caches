/**
 * @file
 * @brief  Unit tests for caching algorithms
 * @author Victor Baldin
 */
#include <cstddef>
#include <vector>

#include <gtest/gtest.h>

#include "belady_cache.hh"
#include "common.hh"
#include "lfu_cache.hh"

namespace {

std::size_t getLfuHits(std::size_t cache_sz, std::vector<int> keys) {
  caches::LfuCache<int, int> cache{cache_sz};
  std::size_t hits = 0;

  for (const auto& key : keys) {
    if (cache.get(key, common::slowGetPage).second) {
      ++hits;
    }
  }
  return hits;
}

std::size_t getBeladyHits(std::size_t cache_sz, std::vector<int> keys) {
  caches::BeladyCache<int, int> cache{cache_sz, keys.cbegin(), keys.cend()};
  std::size_t hits = 0;

  for (const auto& key : keys) {
    if (cache.get(key, common::slowGetPage).second) {
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
  EXPECT_EQ(getBeladyHits(2, {1, 2, 1, 2, 1, 2}), 4);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
