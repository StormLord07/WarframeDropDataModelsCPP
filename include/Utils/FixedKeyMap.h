
#include <map>
#include <unordered_map>

template <typename K, typename V> class FixedKeyMap {
public:
  explicit FixedKeyMap(std::initializer_list<K> keys) {
    for (const auto &key : keys) {
      map_.emplace(key, V{});
    }
  }

  FixedKeyMap() = default;

  V &operator[](const K &key) { return this->map_.at(key); }

  const V &at(const K &key) const { return this->map_.at(key); }

  bool contains(const K &key) const { return this->map_.contains(key); }

  auto begin() const { return this->map_.begin(); }
  auto end() const { return this->map_.end(); }

  auto begin() { return this->map_.begin(); }
  auto end() { return this->map_.end(); }

private:
  std::map<K, V> map_;
};

template <typename K, typename V> class FixedKeyUMap {
public:
  explicit FixedKeyUMap(std::initializer_list<K> keys) {
    for (const auto &key : keys) {
      map_.emplace(key, V{});
    }
  }

  FixedKeyUMap() = default;

  V &operator[](const K &key) { return this->map_.at(key); }

  const V &at(const K &key) const { return this->map_.at(key); }

  bool contains(const K &key) const { return this->map_.contains(key); }

  auto begin() const { return this->map_.begin(); }
  auto end() const { return this->map_.end(); }

  auto begin() { return this->map_.begin(); }
  auto end() { return this->map_.end(); }

private:
  std::unordered_map<K, V> map_;
};
