/**
 * @file
 * @brief  Interface header for the cache library.
 * @author Victor Baldin
 */
#ifndef PROBLEM_LC_BELADY_CACHE_HH_
#define PROBLEM_LC_BELADY_CACHE_HH_

#include <cstddef>
#include <deque>
#include <unordered_map>

namespace caches {

template <typename T, typename KeyT>
class BeladyCache {
  std::size_t sz_;
  std::unordered_map<KeyT, T> lookup_table_;
  std::deque<KeyT> expected_keys_;

  bool full() const noexcept {
    return lookup_table_.size() == sz_;
  }

  void popElem() noexcept {

  }

  void insertElem(std::pair<KeyT, T> elem) {
    lookup_table_.insert(elem);
  }

 public:
  template <typename It>
  BeladyCache(std::size_t sz, It begin, It end) : sz_(sz) {
    for (auto it = begin; it != end; ++it) {
      expected_keys_.push_back(*it);
    }
  }

  template <typename GetterT>
  std::pair<T, bool> get(KeyT key, GetterT getter) {
    auto match = lookup_table_.find(key);
    expected_keys_.pop_front();  // сдвигаемся на 1

    if (match == lookup_table_.end()) {
      if (full()) {
        popElem();
      }
      T page = getter(key);
      insertElem(std::make_pair(key, page));
      return std::make_pair(page, false);
    }

    return std::make_pair(match->second, true);
  }
};

}  // namespace caches

#endif  // PROBLEM_LC_BELADY_CACHE_HH_
