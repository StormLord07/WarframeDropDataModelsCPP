#ifndef WARFRAME_API_MANIFEST_EXPORT_RELIC_RESOURCES_H
#define WARFRAME_API_MANIFEST_EXPORT_RELIC_RESOURCES_H

#include <optional>
#include <string>
#include <vector>

namespace Warframe::Manifest {
namespace Model {

struct RelicResources {
  std::string uniqueName{};
  std::string name{};
  std::string description{};
  bool codexSecret{};
  std::string parentName{}; // Relative path to parent resource data
  bool excludeFromCodex{};
  std::optional<bool> showInInventory{};
};

} // namespace Model

namespace Export {

struct Resources {
  std::vector<Model::RelicResources> ExportRelicResources{};
};

} // namespace Export
} // namespace Warframe::Manifest

#endif // WARFRAME_API_MANIFEST_EXPORT_RELIC_RESOURCES_H
