#ifndef WARFRAME_API_MANIFEST_EXPORT_FUSION_BUNDLES_H
#define WARFRAME_API_MANIFEST_EXPORT_FUSION_BUNDLES_H

#include <string>
#include <vector>

namespace Warframe::Manifest {
namespace Model {

struct FusionBundles {
  std::string uniqueName{};
  std::string description{};
  bool codexSecret{};
  int fusionPoints{};
};

} // namespace Model

namespace Export {

struct FusionBundles {
  std::vector<Model::FusionBundles> ExportFusionBundles{};
};

} // namespace Export
} // namespace Warframe::Manifest

#endif // WARFRAME_API_MANIFEST_EXPORT_FUSION_BUNDLES_H