#ifndef TRANSIENT_MODEL_H
#define TRANSIENT_MODEL_H

#include <glaze/glaze.hpp>
#include <optional>
#include <string>

#include "RewardModel.h"

namespace transient {

enum class ROTATION { A, B, C };

struct RewardItem {
  std::string _id;
  std::string itemName;
  std::optional<ROTATION> rotation;
  reward::RARITY rarity;
  double chance;
};

} // namespace transient

template <> struct glz::meta<transient::ROTATION> {
  using enum transient::ROTATION;
  static constexpr auto value = glz::enumerate(A, B, C);
};

struct TransientReward {
  std::string _id;
  std::string objectiveName;
  std::vector<transient::RewardItem> rewards;
};

#endif // TRANSIENT_MODEL_H