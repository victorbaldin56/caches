/**
 * @file
 * @brief  Driver for Belady cache.
 * @author Victor Baldin
 */
#include <iostream>
#include <vector>

#include "belady_cache.hh"
#include "common.hh"

namespace {

std::vector<int> getInputKeys(std::size_t count) {
  std::vector<int> ret;

  for (std::size_t i = 0; i < count; ++i) {
    int key = 0;
    std::cin >> key;
    ret.push_back(key);
  }
  return ret;
}

}  // namespace

int main() {
  std::size_t cache_sz = 0, elem_count = 0;
  std::cin >> cache_sz >> elem_count;

  std::vector<int> keys = getInputKeys(elem_count);
  caches::BeladyCache<int, int> cache{cache_sz, keys.cbegin(), keys.cend()};

  std::size_t hits = 0;
  for (auto& key : keys) {
    if (cache.get(key, common::slowGetPage).second) {
      ++hits;
    }
  }

  std::cout << hits << "\n";
  return 0;
}
