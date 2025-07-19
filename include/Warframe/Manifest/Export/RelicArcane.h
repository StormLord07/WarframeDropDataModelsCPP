#ifndef WARFRAME_API_MANIFEST_EXPORT_RELIC_ARCANE_H
#define WARFRAME_API_MANIFEST_EXPORT_RELIC_ARCANE_H

#include <array>
#include <compare>
#include <string>
#include <variant>
#include <vector>

#include "Warframe/Manifest/Export/Generic.h"

namespace Warframe::Manifest {
namespace Model {

struct RelicReward {
  std::string rewardName{};
  RARITY rarity{};
  int tier{};
  int itemCount{}; // Number of items in the reward

  auto operator<=>(const RelicReward &) const = default;
};

struct Relic {
  std::string uniqueName{};
  std::string name{};
  std::string description{};
  bool codexSecret{};
  std::vector<RelicReward> relicRewards{};
  auto operator<=>(const Relic &) const = default;
};

struct Arcane {
  std::string uniqueName{};
  std::string name{};
  bool codexSecret{};
  RARITY rarity{};
  std::vector<LevelStats> levelStats{};
  auto operator<=>(const Arcane &) const = default;
};

using RelicArcane = std::variant<Relic, Arcane>;

} // namespace Model

namespace Export {

struct RelicArcane {
  std::vector<Model::RelicArcane> ExportRelicArcane{};
};

} // namespace Export
} // namespace Warframe::Manifest

#endif // WARFRAME_API_MANIFEST_EXPORT_RELIC_ARCANE_H