/**
 * @file
 * @brief Interface header for the cache library.
 * @author Victor Baldin
 */
#ifndef PROBLEM_LC_LFU_CACHE_HH_
#define PROBLEM_LC_LFU_CACHE_HH_

#include <cstddef>
#include <queue>
#include <unordered_map>

namespace caches {

/**
 * Cache implementation based on LFU (least-frequently used) caching policy.
 */
template <typename T, typename KeyT>
class LfuCache final {
  struct Elem {
    T page_;
    std::size_t ref_count_;  ///< ref count for the given page
  };

  std::unordered_map<KeyT, Elem> lookup_table_;
  std::size_t sz_;  ///< cache size

  std::size_t getRefCount(KeyT key) const noexcept {
    return lookup_table_[key].ref_count_;
  }

  struct LfuComparator {
    LfuCache<T, KeyT>* cache_ptr_;

    bool operator()(const KeyT& lhs, const KeyT& rhs) {
      return cache_ptr_->getRefCount(lhs) > cache_ptr_->getRefCount(rhs);
    }
  } lfu_cmp_;

  std::priority_queue<KeyT, std::vector<KeyT>, LfuComparator> page_queue_;

  bool full() const noexcept { return lookup_table_.size() == sz_; }

 public:
  LfuCache(std::size_t sz) noexcept : sz_(sz), lfu_cmp_({this}) {}

  template <typename GetterT>
  bool get(KeyT key, GetterT slow_page_getter) {
    auto match = lookup_table_.find(key);

    // page not found in cache
    if (match == lookup_table_.end()) {
      if (full()) {
        page_queue_.pop();
      }
      page_queue_.push(key);
      lookup_table_.insert(key, {slow_page_getter(key), 1});
      return false;
    }

    ++match->second.ref_count;
    return true;
  }
};

}  // namespace caches

#endif  // PROBLEM_LC_LFU_CACHE_HH_
