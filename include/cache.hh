/**
 * @file
 * @brief Interface header for the cache library.
 * @author Victor Baldin
 */
#ifndef PROBLEM_LC_CACHE_HH_
#define PROBLEM_LC_CACHE_HH_

#include <cstddef>
#include <list>
#include <unordered_map>

namespace cache {

/**
 * @brief
 */
template <typename PageT, typename KeyT>
class Cache {
  std::size_t sz_;  ///< cache size
  std::list<PageT> pages_;

  using PageIt = typename std::list<PageT>::iterator;
  std::unordered_map<KeyT, PageIt> lookup_table_;

  bool full() const noexcept { return lookup_table_.size() == sz_; }
  void removePage() noexcept {}

 public:
  Cache(std::size_t sz) noexcept : sz_(sz) {}

  template <typename GetterT>
  bool getPage(KeyT key, GetterT slow_page_getter) {
    auto match = lookup_table_.find(key);
    if (match == lookup_table_.end()) {
      if (full()) {
        removePage();
      }
      slow_page_getter(key);
    }

    return true;
  }
};

}  // namespace cache

#endif  // PROBLEM_LC_CACHE_HH_
