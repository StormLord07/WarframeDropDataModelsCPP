#ifndef HUB_REWARD_MODEL_H
#define HUB_REWARD_MODEL_H

#include "RewardModel.h"

namespace hub {
struct RewardItem {
  std::string _id;
  std::string itemName;
  reward::RARITY rarity;
  std::string stage;
  double chance;
};

struct Rewards {
  std::vector<RewardItem> A;
  std::vector<RewardItem> B;
  std::vector<RewardItem> C;
};

} // namespace hub

struct HubReward {
  std::string _id;
  std::string bountyLevel;
  hub::Rewards rewards;
};

#endif // HUB_REWARD_MODEL_H