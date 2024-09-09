#include <iostream>

#include "lfu_cache.hh"

static std::vector<int> g_keyTable = {};

int main() {
  std::size_t cache_sz = 0, elem_count = 0;
  std::cin >> cache_sz >> elem_count;
  for (std::size_t i = 0; i < elem_count; ++i) {
    std::cin >> g_keyTable[i];
  }

  caches::LfuCache<int, int> cache{cache_sz};
  return 0;
}
