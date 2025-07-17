#ifndef STARCHART_EVENT_MODEL_H
#define STARCHART_EVENT_MODEL_H

#include "RewardModel.h"
#include <string>

struct SortieReward {
  std::string _id;
  std::string itemName;
  reward::RARITY rarity;
  double chance;
};

struct KeyReward {
  std::string _id;
  std::string keyName;
  Rewards rewards; // where Rewards = { A: [...], B: [...], C: [...] }
};

#endif // STARCHART_EVENT_MODEL_H