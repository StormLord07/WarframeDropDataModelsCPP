#ifndef WARFRAME_API_MANIFEST_EXPORT_GEAR_H
#define WARFRAME_API_MANIFEST_EXPORT_GEAR_H

#include "Warframe/Manifest/Export/Generic.h"

#include <string>
#include <vector>

namespace Warframe::Manifest {
namespace Model {

using Gear = Generic;

} // namespace Model

namespace Export {

struct Gear {
  std::vector<Model::Gear> ExportGear{};
};

} // namespace Export
} // namespace Warframe::Manifest

#endif // WARFRAME_API_MANIFEST_EXPORT_GEAR_H