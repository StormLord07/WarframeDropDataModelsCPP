#ifndef WARFRAME_API_MANIFEST_EXPORT_GENERIC_H
#define WARFRAME_API_MANIFEST_EXPORT_GENERIC_H

#include <compare>
#include <optional>
#include <string>
#include <vector>

namespace Warframe::Manifest {
namespace Model {

enum class RARITY { Common, Uncommon, Rare, Legendary };

enum class POLARITY {
  AP_POWER,
  AP_DEFENSE,
  AP_TACTIC,
  AP_ATTACK,
  AP_WARD,
  AP_UNIVERSAL
};

// TODO: productCategory to enum

struct Generic {
  std::string uniqueName{};
  std::string name{};
  std::string description{};
  bool codexSecret{};
  std::optional<bool> excludeFromCodex{};
  std::string parentName{};
};

struct LevelStats {
  std::vector<std::string> stats;
  auto operator<=>(const LevelStats &) const = default;
};

} // namespace Model

} // namespace Warframe::Manifest

#endif // WARFRAME_API_MANIFEST_EXPORT_GENERIC_H