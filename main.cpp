#include "Warframe/Models.h"
#include <algorithm>
#include <fstream>
#include <glaze/glaze.hpp>
#include <iostream>
#include <map>
#include <set>
#include <sstream>

void print_stats(const DropTableData &data) {
  std::cout << "=== Drop Table Statistics ===\n";

  std::cout << "\n-- Mission Rewards --\n";
  size_t total_missions = 0;
  for (const auto &planet :
       {data.missionRewards.Mercury,   data.missionRewards.Venus,
        data.missionRewards.Earth,     data.missionRewards.Mars,
        data.missionRewards.Jupiter,   data.missionRewards.Saturn,
        data.missionRewards.Uranus,    data.missionRewards.Neptune,
        data.missionRewards.Pluto,     data.missionRewards.Ceres,
        data.missionRewards.Eris,      data.missionRewards.Sedna,
        data.missionRewards.Europa,    data.missionRewards.Void,
        data.missionRewards.Phobos,    data.missionRewards.Deimos,
        data.missionRewards.Lua,       data.missionRewards.KuvaFortress,
        data.missionRewards.Sanctuary, data.missionRewards.Veil,
        data.missionRewards.Zariman,   data.missionRewards.Hyollvania,
        data.missionRewards.Duviri}) {
    total_missions += planet.size();
  }
  std::cout << "Total missions across all planets: " << total_missions << "\n";

  std::cout << "\n-- Relics --\n";
  std::cout << "Relic count: " << data.relics.size() << "\n";

  std::map<relic::TIER, size_t> relic_tier_count;
  for (const auto &relic : data.relics) {
    relic_tier_count[relic.tier]++;
  }
  for (const auto &[tier, count] : relic_tier_count) {
    std::cout << "  Tier " << glz::write_json(tier).value() << ": " << count
              << "\n";
  }

  std::cout << "\n-- Transient Rewards --\n";
  std::cout << "Transient objectives: " << data.transientRewards.size() << "\n";

  std::cout << "\n-- Mods --\n";
  std::cout << "Mod Locations: " << data.modLocations.size() << "\n";
  std::cout << "Enemy Mod Tables: " << data.enemyModTables.size() << "\n";

  std::cout << "\n-- Blueprints --\n";
  std::cout << "Blueprint Locations: " << data.blueprintLocations.size()
            << "\n";
  std::cout << "Enemy Blueprint Tables: " << data.enemyBlueprintTables.size()
            << "\n";

  std::cout << "\n-- Special Mission Rewards --\n";
  std::cout << "Sortie Rewards: " << data.sortieRewards.size() << "\n";
  std::cout << "Key Rewards: " << data.keyRewards.size() << "\n";

  std::cout << "\n-- Hub Rewards --\n";
  std::cout << "Cetus: " << data.cetusBountyRewards.size() << "\n";
  std::cout << "Solaris: " << data.solarisBountyRewards.size() << "\n";
  std::cout << "Deimos: " << data.deimosRewards.size() << "\n";
  std::cout << "Zariman: " << data.zarimanRewards.size() << "\n";
  std::cout << "Entrati: " << data.entratiLabRewards.size() << "\n";
  std::cout << "Hex: " << data.hexRewards.size() << "\n";

  std::cout << "\n-- Avatars --\n";
  std::cout << "Resource by Avatar: " << data.resourceByAvatar.size() << "\n";
  std::cout << "Sigil by Avatar: " << data.sigilByAvatar.size() << "\n";
  std::cout << "Additional Items by Avatar: "
            << data.additionalItemByAvatar.size() << "\n";

  std::cout << "\n-- Syndicates --\n";
  size_t syndicate_total = 0;
  glz::for_each_field(data.syndicates, [&](const auto &field) {
    syndicate_total += field.size();
  });
  std::cout << "Total syndicate rewards: " << syndicate_total << "\n";

  std::cout << "\n-- Summary --\n";
  std::cout << "DropTableData Size (elements): " << data.size() << "\n";
}

int main() {
  DropTableData data;
  std::ifstream file("./all.json");
  if (!file) {
    std::cerr << "Failed to open all.json" << std::endl;
    return 1;
  }
  std::stringstream buffer;
  buffer << file.rdbuf();
  std::string json = buffer.str();
  auto ec = glz::read<glz::opts{.error_on_missing_keys = true}>(data, json);
  if (ec) {
    std::cerr << "Failed to parse all.json: " << glz::format_error(ec, json)
              << std::endl;
    return 1;
  }
  for (auto it : data.enemyBlueprintTables) {
    if (!areVectorsEqual(it.items, it.mods)) {
      std::cerr << "mods and items are not equivalent\n";
    }
  }
  print_stats(data);

  return 0;
}