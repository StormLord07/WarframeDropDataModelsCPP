#ifndef SYNDICATE_MODEL_H
#define SYNDICATE_MODEL_H

#include "RewardModel.h"
#include <string>

namespace syndicate {
struct RewardItem {
  std::string _id;
  std::string item;
  double chance;
  reward::RARITY rarity;
  std::string place;
  int standing;
};

struct CostfullRewardItem {
  std::string _id;
  std::string item;
  double chance;
  reward::RARITY rarity;
  std::string place;
  std::optional<int> standing; // the fuck
  std::optional<int> cost;     // inconsistenct is shit
};

} // namespace syndicate

struct Syndicates {
  std::vector<syndicate::RewardItem> SteelMeridian;
  std::vector<syndicate::RewardItem> ArbitersOfHexis;
  std::vector<syndicate::RewardItem> TheQuills;
  std::vector<syndicate::RewardItem> NecraLoid;
  std::vector<syndicate::CostfullRewardItem> OperationalSupply;
  std::vector<syndicate::RewardItem> VoxSolaris;
  std::vector<syndicate::RewardItem> CephalonSimaris;
  std::vector<syndicate::RewardItem> RedVeil;
  std::vector<syndicate::RewardItem> ThePerrinSequence;
  std::vector<syndicate::RewardItem> NewLoka;
  std::vector<syndicate::RewardItem> SolarisUnited;
  std::vector<syndicate::CostfullRewardItem> Entrati;
  std::vector<syndicate::RewardItem> KahlsGarrison;
  std::vector<syndicate::RewardItem> Conclave;
  std::vector<syndicate::RewardItem> Ventkids;
  std::vector<syndicate::RewardItem> CephalonSuda;
  std::vector<syndicate::RewardItem> Ostron;
  std::vector<syndicate::RewardItem> TheHoldfasts;
};

template <> struct glz::meta<Syndicates> {
  using T = Syndicates;
  static constexpr auto value = glz::object(
      "Steel Meridian", &T::SteelMeridian, "Arbiters of Hexis",
      &T::ArbitersOfHexis, "The Quills", &T::TheQuills, "NecraLoid",
      &T::NecraLoid, "Operational Supply", &T::OperationalSupply, "Vox Solaris",
      &T::VoxSolaris, "Cephalon Simaris", &T::CephalonSimaris, "Red Veil",
      &T::RedVeil, "The Perrin Sequence", &T::ThePerrinSequence, "New Loka",
      &T::NewLoka, "Solaris United", &T::SolarisUnited, "Entrati", &T::Entrati,
      "Kahl's Garrison", &T::KahlsGarrison, "Conclave", &T::Conclave,
      "Ventkids", &T::Ventkids, "Cephalon Suda", &T::CephalonSuda, "Ostron",
      &T::Ostron, "The Holdfasts", &T::TheHoldfasts);
};

#endif // SYNDICATE_MODEL_H