/**
 * @file
 * @brief  Driver for LFU cache.
 * @author Victor Baldin
 */
#include <iostream>

#include "common.hh"
#include "lfu_cache.hh"

int main() {
  std::size_t cache_sz = 0, elem_count = 0;
  std::cin >> cache_sz >> elem_count;
  caches::LfuCache<int, int> cache{cache_sz};

  std::size_t hits = 0;
  for (std::size_t i = 0; i < elem_count; ++i) {
    int key = 0;
    std::cin >> key;
    if (cache.get(key, common::slowGetPage).second) {
      ++hits;
    }
  }

  std::cout << hits << "\n";
  return 0;
}
