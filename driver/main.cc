#include <iostream>

#include "cache.hh"

int main() {
  std::cout << "Hello from LFU cache\n";
  std::size_t cache_sz = 0, elem_count = 0;
  std::cin >> cache_sz >> elem_count;
  cache::Cache<int, int> cache{cache_sz};
  return 0;
}
