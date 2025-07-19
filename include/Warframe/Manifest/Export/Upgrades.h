#ifndef WARFRAME_API_MANIFEST_EXPORT_UPGRADES_H
#define WARFRAME_API_MANIFEST_EXPORT_UPGRADES_H

#include <compare>
#include <string>
#include <variant>
#include <vector>

#include "Warframe/Manifest/Export/Generic.h"

namespace Warframe::Manifest {
namespace Model {

struct UpgradeMod {
  std::string uniqueName;
  std::string name;
  POLARITY polarity;
  RARITY rarity;
  bool codexSecret = false;
  int baseDrain = 0;
  int fusionLimit = 0;
  bool isUtility = false;
  std::string compatName;
  std::string type;
  std::vector<LevelStats> levelStats;
  auto operator<=>(const UpgradeMod &) const = default;
};

// Rivens
struct UpgradeValues {
  double value{};
  std::string locTag{};

  auto operator<=>(const UpgradeValues &) const = default;
};

struct UpgradeEntries {
  std::string tag{};
  std::string prefixTag{};
  std::string suffixTag{};
  std::vector<UpgradeValues> upgradeValues{};

  auto operator<=>(const UpgradeEntries &) const = default;
};

struct Complications {
  std::string fullName{};
  std::string description{};
  std::string overrideTag{};

  auto operator<=>(const Complications &) const = default;
};

struct AvailableChallenges {
  std::string fullName{};
  std::string description{};
  std::vector<Complications> complications{};

  auto operator<=>(const AvailableChallenges &) const = default;
};

struct UpgradeRiven {
  std::string uniqueName{};
  std::string name{};
  POLARITY polarity{};
  RARITY rarity{};
  bool codexSecret{};
  int baseDrain{};
  int fusionLimit{};
  bool excludeFromCodex{};
  std::vector<UpgradeEntries> upgradeEntries{};
  std::vector<AvailableChallenges> availableChallenges{};
  auto operator<=>(const UpgradeRiven &) const = default;
};

using Upgrades = std::variant<UpgradeMod, UpgradeRiven>;

// ExportFocusUpgrades

struct FocusUpgrade {
  std::string uniqueName{};
  std::string name{};
  POLARITY polarity{};
  RARITY rarity{};
  bool codexSecret{};
  int baseDrain{};
  int fusionLimit{};
  bool excludeFromCodex{};
  std::vector<LevelStats> levelStats{};
};

// ExportAvionics
struct Avionics {
  std::string uniqueName{};
  std::string name{};
  POLARITY polarity{};
  RARITY rarity{};
  bool codexSecret{};
  int baseDrain{};
  int fusionLimit{};
  std::vector<LevelStats> levelStats{};
};

// ExportModSets
struct Sets {
  std::string uniqueName{};
  int numUpgradesInSet{};
  std::vector<std::string> stats{};
};
} // namespace Model

namespace Export {

struct Upgrades {
  std::vector<Model::Upgrades> ExportUpgrades{};
  std::vector<Model::FocusUpgrade> ExportFocusUpgrades;
  std::vector<Model::Avionics> ExportAvionics;
  std::vector<Model::Sets> ExportModSet;
};

} // namespace Export
} // namespace Warframe::Manifest

#endif // WARFRAME_API_MANIFEST_EXPORT_UPGRADES_H