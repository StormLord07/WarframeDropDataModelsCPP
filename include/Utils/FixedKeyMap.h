#ifndef UTILS_FIXEDKEYMAP_H
#define UTILS_FIXEDKEYMAP_H

#include <map>
#include <unordered_map>

template <template <class, class> class MapType, class K, class V>
class FixedKeyMapImpl {
public:
  explicit FixedKeyMapImpl(std::initializer_list<K> keys) {
    for (const auto &key : keys) {
      map_.emplace(key, V{});
    }
  }

  FixedKeyMapImpl() = delete;

  V &operator[](const K &key) { return this->map_.at(key); }

  const V &at(const K &key) const { return this->map_.at(key); }

  size_t size() const { return this->map_.size(); }

  bool contains(const K &key) const { return this->map_.contains(key); }

  auto begin() const { return this->map_.begin(); }
  auto end() const { return this->map_.end(); }

  auto begin() { return this->map_.begin(); }
  auto end() { return this->map_.end(); }

private:
  MapType<K, V> map_;
};

template <class K, class V> using FixedKeyMap = FixedKeyMapImpl<std::map, K, V>;

template <class K, class V>
using FixedKeyUMap = FixedKeyMapImpl<std::unordered_map, K, V>;

#endif // UTILS_FIXEDKEYMAP_H