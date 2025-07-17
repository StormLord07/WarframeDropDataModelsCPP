#ifndef MODEL_H
#define MODEL_H

#include "Warframe/Models/AvatarModel.h"
#include "Warframe/Models/BlueprintModel.h"
#include "Warframe/Models/HubRewardModel.h"
#include "Warframe/Models/ModModel.h"
#include "Warframe/Models/RelicModel.h"
#include "Warframe/Models/RewardModel.h"
#include "Warframe/Models/StarchartEventModel.h"
#include "Warframe/Models/StarchartModel.h"
#include "Warframe/Models/SyndicatesModel.h"
#include "Warframe/Models/TransientModel.h"

// #include "RewardModel.h"

struct DropTableData {
  Planets missionRewards;
  std::vector<Relic> relics;
  std::vector<TransientReward> transientRewards;
  std::vector<ModLocation> modLocations;
  std::vector<EnemyModTable> enemyModTables;
  std::vector<BlueprintLocation> blueprintLocations;
  std::vector<EnemyBlueprintTable> enemyBlueprintTables;
  std::vector<SortieReward> sortieRewards;
  std::vector<KeyReward> keyRewards;
  std::vector<HubReward> cetusBountyRewards;
  std::vector<HubReward> solarisBountyRewards;
  std::vector<HubReward> deimosRewards;
  std::vector<HubReward> zarimanRewards;
  std::vector<HubReward> entratiLabRewards;
  std::vector<HubReward> hexRewards;
  Syndicates syndicates;
  std::vector<ResourceAvatar> resourceByAvatar;
  std::vector<ResourceAvatar> sigilByAvatar;
  std::vector<ResourceAvatar> additionalItemByAvatar;

  size_t size() const;
};

template <typename T> size_t recursive_size(const T &val);

template <typename T> size_t container_size(const T &container) {
  size_t total = 0;
  for (const auto &elem : container) {
    total += recursive_size(elem);
  }
  return total;
}

template <typename T> size_t recursive_size(const T &val) {
  if constexpr (std::is_same_v<T, std::string>) {
    return val.size(); // Actual character count
  } else if constexpr (glz::glaze_object_t<T> || glz::reflectable<T>) {
    size_t total = 0;
    glz::for_each_field(
        val, [&](const auto &field) { total += recursive_size(field); });
    return total;
  } else if constexpr (requires { val.size(); }) {
    return container_size(val);
  } else {
    return sizeof(T);
  }
}

size_t DropTableData::size() const { return recursive_size(*this); }

#endif // MODEL_H