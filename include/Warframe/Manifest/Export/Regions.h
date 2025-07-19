#ifndef WARFRAME_API_MANIFEST_EXPORT_REGIONS_H
#define WARFRAME_API_MANIFEST_EXPORT_REGIONS_H

#include <string>
#include <vector>

namespace Warframe::Manifest {
namespace Model {

struct Regions {
  std::string uniqueName{};
  std::string name{};
  int systemIndex{};
  std::string systemName{};
  int nodeType{}; // 0 for planet, 1 for junction, etc.
  int masteryReq{};
  int missionIndex{}; // Index of the mission type
  int factionIndex{}; // Index of the faction
  int minEnemyLevel{};
  int maxEnemyLevel{};
};

} // namespace Model

namespace Export {

struct Regions {
  std::vector<Model::Regions> ExportRegions{};
};

} // namespace Export
} // namespace Warframe::Manifest

#endif // WARFRAME_API_MANIFEST_EXPORT_REGIONS_H
