
#ifndef WARFRAME_API_MANIFEST_EXPORT_CUSTOMS_H
#define WARFRAME_API_MANIFEST_EXPORT_CUSTOMS_H

#include <optional>
#include <string>
#include <vector>

#include "Manifest/Export/Generic.h"

namespace Warframe::Manifest {
namespace Model {
// struct Customs {
//   std::string uniqueName{};
//   std::string name{};
//   std::string description{};
//   bool codexSecret{};
//   std::optional<bool> excludeFromCodex{};
// };

using Customs = Generic;

} // namespace Model
namespace Export {

struct Customs {
  std::vector<Model::Customs> ExportCustoms{};
};
} // namespace Export

} // namespace Warframe::Manifest

#endif // WARFRAME_API_MANIFEST_EXPORT_CUSTOMS_H