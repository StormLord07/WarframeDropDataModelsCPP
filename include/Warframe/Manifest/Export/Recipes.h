#ifndef WARFRAME_API_MANIFEST_EXPORT_RECIPES_H
#define WARFRAME_API_MANIFEST_EXPORT_RECIPES_H

#include <optional>
#include <string>
#include <vector>


namespace Warframe::Manifest {
namespace Model {

struct Ingredient {
  std::string ItemType{};
  int ItemCount{};
  std::string ProductCategory{};
};

struct Recipes {
  std::string uniqueName{};
  std::string resultType{};
  int buildPrice{};
  int buildTime{};
  int skipBuildTimePrice{};
  bool consumeOnUse{};
  int num{};
  bool codexSecret{};
  std::optional<int> primeSellingPrice{};
  bool excludeFromCodex{};
  std::vector<Ingredient> ingredients{};
  std::vector<Ingredient> secretIngredients{}; // List of secret ingredients
};

} // namespace Model

namespace Export {

struct Recipes {
  std::vector<Model::Recipes> ExportRecipes{};
};

} // namespace Export
} // namespace Warframe::Manifest

#endif // WARFRAME_API_MANIFEST_EXPORT_RECIPES_H