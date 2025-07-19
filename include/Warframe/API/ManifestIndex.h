#ifndef WARFRAME_API_MANIFEST_INDEX_H
#define WARFRAME_API_MANIFEST_INDEX_H

#include "Utils/Error.h"
#include "Utils/FixedKeyMap.h"
#include "Utils/Utils.h"

#include <cpr/cpr.h>
#include <lzma.h>

#include <expected>
#include <filesystem>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <string>
#include <string_view>
#include <thread>
#include <unordered_map>
#include <vector>

// https://wiki.warframe.com/w/Public_Export#Generic_Entry_Schema
namespace public_export {

struct Info {
  std::string filename;
  std::string hash;

  explicit operator std::string() const { return filename + "!" + hash; }
};

struct Data {
  std::string filename;
  Info customs; // Warframe Cosmetics, Weapon skins, Companion skins, Archwing
                // cosmetics, Operator cosmetics, Necramech cosmetics, K-Drive
                // cosmetics, Animation Sets, TennoGen skins, Sigils, Sugatras
                // (ExportCustoms)
  Info drones;  // Extractors (ExportDrones)
  Info flavour; // Player customizable content (Glyphs, Color Picker Extension,
                // Decorations, Landing Craft skins, Animation Sets, menu
                // themes, etc.) (ExportFlavour)
  Info fusion_bundles; // Mod bundles in the Market (ExportFusionBundles)
  Info gear; // Gear items, including Fishing and Conservation related items
             // (ExportGear)
  Info keys; // Mission keys (e.g. Mutalist Alad V Assassinate Key) and Quests
             // (ExportKeys)
  Info recipes;      // Blueprints (ExportRecipes)
  Info regions;      // Star Chart nodes (ExportRegions)
  Info relic_arcane; // Void Relics and Arcane Enhancements (ExportRelicArcane)
  Info resources;    // 	Resources, Fishing resources, Mining resources, Captura
                     // scenes, ship decorations, components, and other items
                     // (ExportResources)
  Info sentinels;    // 	Sentinels, Kubrows, Kavats, Predasites, Vulpaphylas
                     // (ExportSentinels)
  Info sortie_rewards; // Sortie rewards (ExportSortieRewards)
                       // Nightwave challenges (ExportNightwave)
                       // Veil Proxima nodes for Sentient anomaly
                       // (ExportRailjack) Intrinsics (ExportIntrinsics)
                       // Boosters, Gene-Masking Kits, misc. (ExportOther)
  Info upgrades;       // Upgrades:
                 // Mods, Riven Mods challenges and base stats (ExportUpgrades)
                 // Focus nodes (ExportFocusUpgrades)
                 // Plexus mods (ExportAvionics)
                 // Set Mods (ExportModSet)
  Info warframes; // Warframes, Archwings, Necramechs (ExportWarframes)
                  // Helminth abilities (ExportAbilities)
  Info weapons;   // Weapons, Exalted Weapons, modular weapon parts (Amps, Zaws,
                  // Kitguns), modular companion parts (MOA (Companion),
                  // Predasite, Vulpaphyla, Hound (Companion)), modular K-Drives
                  // parts (ExportWeapons)
                  // Railjack Armaments (ExportRailjackWeapons)
  Info manifest;  // Full image manifest (same for all languages)

  static std::expected<public_export::Data, std::string>
  parse(const std::vector<std::string> &data);

  using FieldEntry = std::pair<std::string_view, Info Data::*>;

  // Static table mapping names to member pointers
  static constexpr FieldEntry field_table[] = {
      {"ExportCustoms", &Data::customs},
      {"ExportDrones", &Data::drones},
      {"ExportFlavour", &Data::flavour},
      {"ExportFusionBundles", &Data::fusion_bundles},
      {"ExportGear", &Data::gear},
      {"ExportKeys", &Data::keys},
      {"ExportRecipes", &Data::recipes},
      {"ExportRegions", &Data::regions},
      {"ExportRelicArcane", &Data::relic_arcane},
      {"ExportResources", &Data::resources},
      {"ExportSentinels", &Data::sentinels},
      {"ExportSortieRewards", &Data::sortie_rewards},
      {"ExportUpgrades", &Data::upgrades},
      {"ExportWarframes", &Data::warframes},
      {"ExportWeapons", &Data::weapons},
      {"ExportManifest", &Data::manifest},
  };

  // Iterators over the static table
  static constexpr auto begin() noexcept { return std::begin(field_table); }
  static constexpr auto end() noexcept { return std::end(field_table); }

  explicit operator std::string() const {
    std::string rv;
    if (!this->filename.empty()) {
      for (const auto &[_, value] : *this) {
        rv += (this->*value).filename + "!" + (this->*value).hash + "\n";
      }
      rv.pop_back();
      return rv;
    }
    return {};
  }
};

} // namespace public_export

class ManifestIndex {
public:
  ManifestIndex(std::initializer_list<std::string> languages = {
                    "de", "en", "es", "fr", "it", "ja", "ko", "pl", "pt", "ru",
                    "tc", "th", "tr", "uk", "zh"});

  ManifestIndex(const ManifestIndex &) = default;
  ManifestIndex(ManifestIndex &&) = default;

  std::expected<public_export::Data, ExpectedErrorType>
  get(std::string language);
  std::expected<void, ExpectedErrorType> get();
  std::expected<void, ExpectedErrorType> getProgressBar();

  std::expected<void, ExpectedErrorType>
  save(std::string_view data, const std::filesystem::path &path);
  std::expected<void, ExpectedErrorType> save();

  std::expected<void, ExpectedErrorType> load();
  std::expected<public_export::Data, ExpectedErrorType>
  load(const std::filesystem::path &path);

  std::expected<void, ExpectedErrorType>
  tryLoad(); // Try to load the index, if it fails, try to download it

  FixedKeyUMap<std::string, public_export::Data> language_index;

private:
  std::vector<std::string> lzma24_decompress(const std::string_view data);
  static const std::string base_url_;

  cpr::Session session_;
};

#endif // WARFRAME_API_MANIFEST_INDEX_H