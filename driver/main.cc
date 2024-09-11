#include <cstdlib>
#include <iostream>

#include "lfu_cache.hh"
#include "testing.hh"

namespace {

// int is a page type in this model
int slowGetPage(int /*key*/) {
  return 0;
}

template <typename CacheT>
std::size_t getCacheHits(CacheT& cache, std::size_t elem_count) {
  std::size_t hit_count = 0;

  for (std::size_t i = 0; i < elem_count; ++i) {
    int key = 0;
    std::cin >> key;
    if (cache.get(key, slowGetPage).second) {
      ++hit_count;
    }
  }
  return hit_count;
}

}  // namespace

TEST(lfu_cache, hits) {
  for (std::size_t i = 0; i < ARRAY_SIZE(caches::testing::g_lfuTests); ++i) {
    const caches::testing::Test& cur_test = caches::testing::g_lfuTests[i];
    caches::LfuCache<int, int> cache{cur_test.elem_count_};

    std::size_t hits = 0;
    for (std::size_t i = 0; i < cur_test.elem_count_; ++i) {
      if (cache.get(cur_test.keys_[i], slowGetPage).second) {
        ++hits;
      }
    }

    EXPECT_EQ(hits, cur_test.hit_count_);
  }
}

int main(int argc, char** argv) {
#ifndef TESTING
  std::size_t cache_sz = 0, elem_count = 0;
  std::cin >> cache_sz >> elem_count;
  caches::LfuCache<int, int> cache{cache_sz};

  std::size_t hit_count = getCacheHits(cache, elem_count);

  std::cout << hit_count << "\n";

#else
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
#endif
}
