#ifndef WARFRAME_API_MANIFEST_EXPORT_KEYS_H
#define WARFRAME_API_MANIFEST_EXPORT_KEYS_H

#include "Warframe/Manifest/Export/Generic.h"

#include <vector>

namespace Warframe::Manifest {
namespace Model {

using Keys = Generic;

} // namespace Model

namespace Export {
struct Keys {
  std::vector<Model::Keys> ExportKeys{};
};

} // namespace Export
} // namespace Warframe::Manifest

#endif // WARFRAME_API_MANIFEST_EXPORT_KEYS_H