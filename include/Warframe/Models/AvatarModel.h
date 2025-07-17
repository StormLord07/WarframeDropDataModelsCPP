#ifndef AVATAR_MODEL_H
#define AVATAR_MODEL_H

#include "RewardModel.h"
#include <string>
#include <vector>

namespace avatar {
struct RewardItem {
  std::string _id;
  std::string item;
  reward::RARITY rarity;
  std::optional<double> chance;
};
} // namespace avatar

struct ResourceAvatar {
  std::string _id;
  std::string source;
  std::vector<avatar::RewardItem> items;
};

#endif // AVATAR_MODEL_H