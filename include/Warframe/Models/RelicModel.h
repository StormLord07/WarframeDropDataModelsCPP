#ifndef RELIC_MODEL_H
#define RELIC_MODEL_H

#include "RewardModel.h"
#include <glaze/glaze.hpp>

namespace relic {

enum class TIER { Lith, Neo, Meso, Axi, Requiem };

enum class STATE { Intact, Exceptional, Flawless, Radiant };

} // namespace relic

template <> struct glz::meta<relic::TIER> {
  using enum relic::TIER;
  static constexpr auto value = glz::enumerate(Lith, Neo, Meso, Axi, Requiem);
};

template <> struct glz::meta<relic::STATE> {
  using enum relic::STATE;
  static constexpr auto value =
      glz::enumerate(Intact, Exceptional, Flawless, Radiant);
};

struct Relic {
  relic::TIER tier;
  relic::STATE state;
  std::string relicName;
  std::vector<RewardItem> rewards;
  std::string _id;
};

#endif // RELIC_MODEL_H