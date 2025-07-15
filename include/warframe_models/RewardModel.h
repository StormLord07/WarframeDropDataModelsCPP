#ifndef REWARD_DATA_MODEL_H
#define REWARD_DATA_MODEL_H

#include <glaze/glaze.hpp>
#include <string>
#include <vector>

namespace reward {
enum class RARITY { Common, Uncommon, Rare, Legendary };
}

template <> struct glz::meta<reward::RARITY> {
  using enum reward::RARITY;
  static constexpr auto value =
      glz::enumerate(Common, Uncommon, Rare, Legendary);
};

struct RewardItem {
  std::string _id;
  std::string itemName;
  reward::RARITY rarity;
  double chance;
};

struct Rewards {
  std::vector<RewardItem> A;
  std::vector<RewardItem> B;
  std::vector<RewardItem> C;
};

#endif // REWARD_DATA_MODEL_H