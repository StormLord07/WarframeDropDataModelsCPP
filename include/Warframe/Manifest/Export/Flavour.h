#ifndef WARFRAME_API_MANIFEST_EXPORT_FLAVOURS_H
#define WARFRAME_API_MANIFEST_EXPORT_FLAVOURS_H

#include <optional>
#include <string>
#include <vector>

namespace Warframe::Manifest {
namespace Model {

struct HexColours {
  std::string value{};
};

struct Flavours {
  std::string uniqueName{};
  std::string name{};
  std::string description{};
  bool codexSecret{};
  std::optional<bool> excludeFromCodex{};
  std::optional<std::vector<HexColours>>
      hexColours{}; // Optional, as not all flavours have colours
};

} // namespace Model

namespace Export {

struct Flavour {
  std::vector<Model::Flavours> ExportFlavour{};
};
} // namespace Export
} // namespace Warframe::Manifest

#endif // WARFRAME_API_MANIFEST_EXPORT_FLAVOURS_H