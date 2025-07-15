#ifndef BLUEPRINT_MODEL_H
#define BLUEPRINT_MODEL_H

#include <glaze/glaze.hpp>
#include <optional>
#include <string>
#include <vector>

#include "RewardModel.h"

namespace blueprint {

struct Enemy {
  std::string _id;
  std::string enemyName;
  double enemyItemDropChance;
  double enemyBlueprintDropChance;
  reward::RARITY rarity;
  double chance;
};

} // namespace blueprint

namespace enemy {

struct DroppedItem {
  std::string _id;
  std::string itemName;
  reward::RARITY rarity;
  double chance;
};

struct DroppedModRemoveLater {
  std::string _id;
  std::string modName;
  reward::RARITY rarity;
  double chance;
};

} // namespace enemy

struct BlueprintLocation {
  std::string _id;
  std::string itemName;
  std::string blueprintName;
  std::vector<blueprint::Enemy> enemies;
};

struct EnemyBlueprintTable {
  std::string _id;
  std::string enemyName;
  std::vector<enemy::DroppedItem> items;
  std::vector<enemy::DroppedModRemoveLater>
      mods; // this seems excessive, we'd need to test out if all of them are
            // equal
};

bool areEqual(const enemy::DroppedItem &a,
              const enemy::DroppedModRemoveLater &b) {
  return a._id == b._id && a.itemName == b.modName && a.rarity == b.rarity &&
         std::abs(a.chance - b.chance) < 1e-6;
}

bool areVectorsEqual(const std::vector<enemy::DroppedItem> &items,
                     const std::vector<enemy::DroppedModRemoveLater> &mods) {
  if (items.size() != mods.size())
    return false;

  return std::equal(items.begin(), items.end(), mods.begin(), areEqual);
}

#endif