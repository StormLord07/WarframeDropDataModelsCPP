#ifndef WARFRAME_API_MANIFEST_EXPORT_DRONES_H
#define WARFRAME_API_MANIFEST_EXPORT_DRONES_H

#include <array>
#include <string>
#include <vector>

namespace Warframe::Manifest {
namespace Model {
struct Drones {
  std::string uniqueName{};
  std::string name{};
  std::string description{};
  //   std::string parentName; // Doesnt seem to be present in the Export
  int binCount{};
  int binCapacity{};
  double fillRate{};
  int durability{};
  int repairRate{};
  bool codexSecret{};
  std::array<int, 4> capacityMultiplier{};
  std::array<int, 0> specialities{};
};
} // namespace Model
namespace Export {

struct Drones {
  std::vector<Model::Drones> ExportDrones{};
};

} // namespace Export

} // namespace Warframe::Manifest

#endif // WARFRAME_API_MANIFEST_EXPORT_DRONES_H