#ifndef MOD_MODEL_H
#define MOD_MODEL_H

#include <glaze/glaze.hpp>
#include <optional>
#include <string>
#include <vector>

namespace mod {

struct Enemy {
  std::string _id;
  std::string enemyName;
  double enemyModDropChance;
  reward::RARITY rarity;
  std::optional<double> chance;
};

} // namespace mod

namespace enemy {

struct DroppedMod {
  std::string _id;
  std::string modName;
  reward::RARITY rarity;
  std::optional<double> chance;
};

} // namespace enemy

struct ModLocation {
  std::string _id;
  std::string modName;
  std::vector<mod::Enemy> enemies;
};

struct EnemyModTable {
  std::string _id;
  std::string enemyName;
#if ASSUME_STRING
  std::string ememyModDropChance;
  std::string enemyModDropChance;
#else
  double ememyModDropChance; // test out equality of ememy and enemy
  double enemyModDropChance;
#endif
  std::vector<enemy::DroppedMod> mods;
};

template <> struct glz::meta<EnemyModTable> {
  using T = EnemyModTable;
  static constexpr auto value = glz::object(
      "_id", &T::_id, "enemyName", &T::enemyName, "ememyModDropChance",
      glz::quoted_num<&T::ememyModDropChance>, "enemyModDropChance",
      glz::quoted_num<&T::enemyModDropChance>, "mods", &T::mods);
};

#endif // MOD_MODEL_H
