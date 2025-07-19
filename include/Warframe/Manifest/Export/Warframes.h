#ifndef WARFRAME_API_MANIFEST_EXPORT_WARFRAMES_H
#define WARFRAME_API_MANIFEST_EXPORT_WARFRAMES_H

#include <array>
#include <string>
#include <vector>

namespace Warframe::Manifest {
namespace Model {

struct Abilities {
  std::string abilityUniqueName{};
  std::string abilityName{};
  std::string description{};
};

struct Avatar {
  std::string uniqueName{};
  std::string name{};
  std::string parentName{};
  std::string description{};

  int health{};
  int shield{};
  int armor{};
  int stamina{}; // Deprecated
  int power{};

  bool codexSecret{};
  int masteryReq{};
  float sprintSpeed{};

  std::string passiveDescription{};
  std::vector<std::string> exalted{};
  std::array<Abilities, 4> abilities{};
  std::string productCategory{};
};

} // namespace Model

namespace Export {

struct Warframes {
  std::vector<Model::Avatar> ExportWarframes{};
  std::array<Model::Abilities, 15> ExportAbilities{};
};

} // namespace Export
} // namespace Warframe::Manifest

#endif // WARFRAME_API_MANIFEST_EXPORT_WARFRAMES_H
