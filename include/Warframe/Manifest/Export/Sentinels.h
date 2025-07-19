#ifndef WARFRAME_API_MANIFEST_EXPORT_SENTINELS_H
#define WARFRAME_API_MANIFEST_EXPORT_SENTINELS_H

#include <string>
#include <vector>

namespace Warframe::Manifest {
namespace Model {

struct Sentinels {
  std::string uniqueName{};
  std::string name{};
  std::string description{};
  int health{};
  int shield{};
  int armor{};
  int stamina{};
  int power{};
  bool codexSecret{};
  std::string productCategory{};
};

} // namespace Model

namespace Export {

struct Sentinels {
  std::vector<Model::Sentinels> ExportSentinels{};
};

} // namespace Export
} // namespace Warframe::Manifest

#endif // WARFRAME_API_MANIFEST_EXPORT_SENTINELS_H