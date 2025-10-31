#ifndef NOOBSTERS_VECTOR_MAP_H
#define NOOBSTERS_VECTOR_MAP_H

#include <algorithm>
#include <concepts>
#include <utility>
#include <vector>



namespace noobsters {
template <std::equality_comparable key_t, typename value_t>
class vector_map : public std::vector<std::pair<key_t, value_t>> {
 private:
  using base_type = std::vector<std::pair<key_t, value_t>>;

 public:
  using base_type::begin;
  using base_type::end;

 public:
  [[nodiscard]] typename base_type::iterator find(const key_t& key) {
    return std::find_if(base_type::begin(), base_type::end(),
                        [&key](const std::pair<key_t, value_t>& element) {
                          return element.first == key;
                        });
  }

  [[nodiscard]] typename base_type::const_iterator find(const key_t& key) const {
    return std::find_if(base_type::begin(), base_type::end(),
                        [&key](const std::pair<key_t, value_t>& element) {
                          return element.first == key;
                        });
  }

  [[nodiscard]] value_t& operator[](const key_t& key) {
    auto found_it = find(key);
    ReturnIf(found_it != base_type::end(), found_it->second);

    return base_type::emplace_back(std::make_pair(key, value_t())).second;
  }
};
}  // namespace noobsters
#endif  // WUNDER_VECTOR_MAP_H
