#ifndef WARFRAME_API_MANIFEST_EXPORT_WEAPONS_H
#define WARFRAME_API_MANIFEST_EXPORT_WEAPONS_H

#include <array>
#include <compare>
#include <string>
#include <variant>
#include <vector>


namespace Warframe::Manifest {
namespace Model {

struct Gun {
  std::string name{};
  std::string uniqueName{};
  bool codexSecret{};
  std::array<float, 20> damagePerShot{};
  float totalDamage{};
  std::string description{};
  float criticalChance{};
  float criticalMultiplier{};
  float procChance{};
  float fireRate{};
  int masteryReq{};
  std::string productCategory{};
  bool excludeFromCodex{};
  int slot{}; // TODO: maybe enum
  float accuracy{};
  float omegaAttenuation{};
  int maxLevelCap{};
  std::string noise{};
  std::string trigger{};
  int magazineSize{};
  float reloadTime{};
  bool sentinel{};
  int multishot{};
  auto operator<=>(const Gun &) const = default;
};

struct Melee {
  std::string name{};
  std::string uniqueName{};
  bool codexSecret{};
  std::array<float, 20> damagePerShot{};
  float totalDamage{};
  std::string description{};
  float criticalChance{};
  float criticalMultiplier{};
  float procChance{};
  float fireRate{};
  int masteryReq{};
  std::string productCategory{};
  bool excludeFromCodex{};
  int slot{};
  float omegaAttenuation{};
  int maxLevelCap{};
  int blockingAngle{};
  int comboDuration{};
  float followThrough{};
  float range{};
  float slamAttack{};
  float slamRadialDamage{};
  float slamRadius{};
  float slideAttack{};
  float heavyAttackDamage{};
  float heavySlamAttack{};
  float heavySlamRadialDamage{};
  float heavySlamRadius{};
  float windUp{};
  auto operator<=>(const Melee &) const = default;
};

} // namespace Model

namespace Export {

struct Weapons {
  std::vector<std::variant<Model::Gun, Model::Melee>> ExportWeapons{};
};

} // namespace Export
} // namespace Warframe::Manifest

#endif // WARFRAME_API_MANIFEST_EXPORT_WEAPONS_H
