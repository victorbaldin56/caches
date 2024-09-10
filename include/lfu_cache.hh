/**
 * @file
 * @brief Interface header for the cache library.
 * @author Victor Baldin
 */
#ifndef PROBLEM_LC_LFU_CACHE_HH_
#define PROBLEM_LC_LFU_CACHE_HH_

#include <cstddef>
#include <map>
#include <unordered_map>

namespace caches {

/**
 * Cache implementation based on LFU (least-frequently used) caching policy.
 */
template <typename T, typename KeyT>
class LfuCache {
  using KeyRefCountIt = typename std::multimap<std::size_t, KeyT>::iterator;

  std::unordered_map<KeyT, T> lookup_table_;
  std::size_t sz_;  ///< cache size

  // TODO: можно ли эффективнее?
  std::multimap<std::size_t, KeyT> to_invalidate_;
  std::unordered_map<KeyT, KeyRefCountIt> ref_counts_;

  bool full() const noexcept {
    return lookup_table_.size() == sz_;
  }

  void insertElem(std::pair<KeyT, T> elem) {
    lookup_table_.insert(elem);
    auto it = to_invalidate_.insert(std::make_pair(1, elem.first));
    ref_counts_.insert(std::make_pair(elem.first, it));
  }

  void popElem() noexcept {
    auto it = to_invalidate_.begin();
    auto key = it->second;
    lookup_table_.erase(key);
    ref_counts_.erase(key);
    to_invalidate_.erase(it);
  }

  void incrementRefCount(KeyT key) {
    auto old_it = ref_counts_.find(key);
    auto old_it_to_invalidate = old_it->second;

    std::size_t old_count = old_it_to_invalidate->first;
    to_invalidate_.erase(old_it_to_invalidate);
    ref_counts_.erase(old_it);

    auto it = to_invalidate_.insert(std::make_pair(old_count + 1, key));
    ref_counts_.insert(std::make_pair(key, it));
  }

 public:
  LfuCache(std::size_t sz) noexcept : sz_(sz) {}

  template <typename GetterT>
  std::pair<T, bool> get(KeyT key, GetterT slow_page_getter) {
    auto match = lookup_table_.find(key);

    // page not found in cache
    if (match == lookup_table_.end()) {
      if (full()) {
        popElem();
      }
      T page = slow_page_getter(key);
      insertElem(std::make_pair(key, page));
      return std::make_pair(page, false);
    }

    incrementRefCount(key);
    return std::make_pair(match->second, true);
  }
};

}  // namespace caches

#endif  // PROBLEM_LC_LFU_CACHE_HH_
