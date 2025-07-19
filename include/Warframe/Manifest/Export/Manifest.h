#ifndef WARFRAME_API_MANIFEST_EXPORT_MANIFEST_H
#define WARFRAME_API_MANIFEST_EXPORT_MANIFEST_H

#include <string>
#include <vector>

namespace Warframe::Manifest {
namespace Model {

struct Manifest {
  std::string uniqueName{};
  std::string textureLocation{};
};

} // namespace Model

struct ExportManifest {
  std::vector<Model::Manifest> Manifest{};
};

} // namespace Warframe::Manifest

#endif // WARFRAME_API_MANIFEST_EXPORT_MANIFEST_H