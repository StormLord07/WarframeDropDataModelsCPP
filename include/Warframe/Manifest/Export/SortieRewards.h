#ifndef WARFRAME_API_MANIFEST_EXPORT_SORTIE_REWARDS_H
#define WARFRAME_API_MANIFEST_EXPORT_SORTIE_REWARDS_H

#include <string>

#include "Warframe/Manifest/Export/Generic.h"

namespace Warframe::Manifest {
namespace Model {

// Export SortieRewards
struct SortieRewards {
  std::string rewardName{};
  int itemCount{};
  double probability{};
  RARITY rarity{};
  int tier{};
};

// Nightwave
struct Challanges {
  std::string uniqueName{};
  std::string name{};
  std::string description{};
  int standing{};
  int required{};
};

struct Rewards {
  std::string uniqueName{};
  int itemCount{};
};

struct Nightwave {
  std::string affiliationTag{};
  std::vector<Challanges> challenges{};
  std::vector<Rewards> rewards{};
};

// Railjack

struct Nodes {
  std::string uniqueName{};
  std::string name{};
};

struct Railjack {
  std::vector<Nodes> nodes{};
};

// Intrinsics

struct Ranks {
  std::string name{};
  std::string description{};
};

struct Intrinsics {
  std::string name{};
  std::vector<Ranks> ranks{};
};

struct Other {
  std::string uniqueName{};
  std::string name{};
  std::string description{};
  int excludeFromCodex{};
};

} // namespace Model

namespace Export {

struct SortieRewards {
  std::vector<Model::SortieRewards> ExportSortieRewards{};
  std::vector<Model::Nightwave> ExportNightwave{};
  std::vector<Model::Railjack> ExportRailjack{};
  std::vector<Model::Intrinsics> ExportIntrinsics{};
  std::vector<Model::Other> ExportOther{};
};

} // namespace Export
} // namespace Warframe::Manifest

#endif // WARFRAME_API_MANIFEST_EXPORT_SORTIE_REWARDS_H