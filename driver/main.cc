#include <cstdlib>
#include <iostream>

#include "lfu_cache.hh"

// int is a page type in this model
static int slowGetPage(int /*key*/) {
  return 0;
}

int main() {
  std::size_t cache_sz = 0, elem_count = 0;
  std::cin >> cache_sz >> elem_count;
  caches::LfuCache<int, int> cache{cache_sz};

  std::size_t hit_count = 0;
  for (std::size_t i = 0; i < elem_count; ++i) {
    int key = 0;
    std::cin >> key;
    if (cache.get(key, slowGetPage).second) {
      ++hit_count;
    }
  }

  std::cout << hit_count << "\n";
  return 0;
}
