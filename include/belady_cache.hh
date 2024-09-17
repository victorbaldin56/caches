/**
 * @file
 * @brief  Interface header for the cache library.
 * @author Victor Baldin
 */
#ifndef PROBLEM_LC_BELADY_CACHE_HH_
#define PROBLEM_LC_BELADY_CACHE_HH_

#include <cstddef>
#include <unordered_map>
#include <vector>

namespace caches {

template <typename T, typename KeyT>
class BeladyCache {
  using IndexIt = typename std::unordered_map<KeyT, std::vector<std::size_t>>::iterator;

  std::size_t sz_;
  std::size_t cur_index_ = 0;

  std::unordered_map<KeyT, T> lookup_table_;
  std::unordered_map<KeyT, std::vector<std::size_t>> indexes_;

  bool full() const noexcept {
    return lookup_table_.size() == sz_;
  }

  void popElem() noexcept {
    std::size_t pending_ind = 0;
    IndexIt to_pop;

    // находим ключ, который дальше всех
    for (auto it = indexes_.begin(); it != indexes_.end(); ++it) {
      auto key = it->first;
      const auto& first_ind = it->second[0];

      if (first_ind > pending_ind &&
          lookup_table_.find(key) != lookup_table_.end()) {
        pending_ind = first_ind;
        to_pop = it;
      }
    }

    KeyT key = to_pop->first;
    indexes_.erase(to_pop);
    lookup_table_.erase(key);
  }

  void insertElem(std::pair<KeyT, T> elem) {
    lookup_table_.insert(elem);
  }

 public:
  template <typename It>
  BeladyCache(std::size_t sz, It begin, It end) : sz_(sz) {
    std::size_t index = 0;

    for (auto it = begin; it != end; ++it) {
      KeyT key = *it;
      auto match = indexes_.find(key);

      if (match == indexes_.end()) {
        indexes_.insert(std::make_pair(key, std::vector<std::size_t>{index}));
      } else {
        match->second.push_back(index);
      }
      ++index;
    }
  }

  template <typename GetterT>
  std::pair<T, bool> get(KeyT key, GetterT getter) {
    auto match = lookup_table_.find(key);

    if (match == lookup_table_.end()) {
      if (full()) {
        popElem();
      }
      T page = getter(key);
      insertElem(std::make_pair(key, page));

      ++cur_index_;
      return std::make_pair(page, false);
    }

    ++cur_index_;
    return std::make_pair(match->second, true);
  }
};

}  // namespace caches

#endif  // PROBLEM_LC_BELADY_CACHE_HH_
