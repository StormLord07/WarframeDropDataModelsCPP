#include "Warframe/API/Client.h"

const std::string WarframeApiClient::base_url_{
    "http://content.warframe.com/PublicExport/Manifest/"};

WarframeApiClient::WarframeApiClient(
    std::initializer_list<std::string> languages)
    : manifest_index_(languages), language_manifest_(languages) {
  session_.SetUrl(base_url_);
};

ManifestIndex &WarframeApiClient::getManifestIndex() { return manifest_index_; }

WarframeApiClient &WarframeApiClient::get() {
  auto manifest = this->manifest_index_.tryLoad();
  if (!manifest) {
    throw std::runtime_error("Failed to load manifest: " + manifest.error());
  }
  for (const auto &[lang, data] : manifest_index_.language_index) {
    Exports &exports = language_manifest_[lang];
    for (const auto &[name, export_data] : data) {
      const public_export::Info &info = data.*export_data;
      const std::string filename = std::string(info);
      this->session_.SetUrl(base_url_ + filename);
      auto response = session_.Get();
      if (response.status_code != 200) {
        throw std::runtime_error("Failed to download " + filename + ": " +
                                 response.error.message);
      }
      if (info.filename == "ExportCustoms_" + lang + ".json") {
        auto er = glz::read<glz::opts{.error_on_missing_keys = true}>(
            exports.customs, response.text);
        if (er) {
          std::cout << glz::format_error(er, response.text) << __LINE__
                    << std::endl;
        }
      } else if (info.filename == "ExportDrones_" + lang + ".json") {
        auto er = glz::read<glz::opts{.error_on_missing_keys = true}>(
            exports.drones, response.text);
        if (er) {
          std::cout << glz::format_error(er, response.text) << __LINE__
                    << std::endl;
        }
      } else if (info.filename == "ExportFlavour_" + lang + ".json") {
        auto er = glz::read<glz::opts{.error_on_missing_keys = true}>(
            exports.flavour, response.text);
        if (er) {
          std::cout << glz::format_error(er, response.text) << __LINE__
                    << std::endl;
        }
      } else if (info.filename == "ExportFusionBundles_" + lang + ".json") {
        auto er = glz::read<glz::opts{.error_on_missing_keys = true}>(
            exports.drones, response.text);
        if (er) {
          std::cout << glz::format_error(er, response.text) << __LINE__
                    << std::endl;
        }
      } else if (info.filename == "ExportGear_" + lang + ".json") {
        auto er = glz::read<glz::opts{.error_on_missing_keys = true}>(
            exports.gear, response.text);
        if (er) {
          std::cout << glz::format_error(er, response.text) << __LINE__
                    << std::endl;
        }
      } else if (info.filename == "ExportKeys_" + lang + ".json") {
        auto er = glz::read<glz::opts{.error_on_missing_keys = true}>(
            exports.keys, response.text);
        if (er) {
          std::cout << glz::format_error(er, response.text) << __LINE__
                    << std::endl;
        }
      } else if (info.filename == "ExportRecipes_" + lang + ".json") {
        auto er = glz::read<glz::opts{.error_on_missing_keys = true}>(
            exports.recipes, response.text);
        if (er) {
          std::cout << glz::format_error(er, response.text) << __LINE__
                    << std::endl;
        }
      } else if (info.filename == "ExportRegions_" + lang + ".json") {
        auto er = glz::read<glz::opts{.error_on_missing_keys = true}>(
            exports.regions, response.text);
        if (er) {
          std::cout << glz::format_error(er, response.text) << __LINE__
                    << std::endl;
        }
      } else if (info.filename == "ExportRelicArcane_" + lang + ".json") {
        // exports.relic_acrane =
        auto er = glz::read<glz::opts{.error_on_missing_keys = true}>(
            exports.relic_acrane, response.text);
        if (er) {
          std::cout << glz::format_error(er, response.text) << __LINE__
                    << std::endl;
        }
      } else if (info.filename == "ExportSentinels_" + lang + ".json") {
        auto er = glz::read<glz::opts{.error_on_missing_keys = true}>(
            exports.sentinels, response.text);
        if (er) {
          std::cout << glz::format_error(er, response.text) << __LINE__
                    << std::endl;
        }
      } else if (info.filename == "ExportSortieRewards_" + lang + ".json") {
        auto er = glz::read<glz::opts{.error_on_missing_keys = true}>(
            exports.sortie_rewards, response.text);
        if (er) {
          std::cout << glz::format_error(er, response.text) << __LINE__
                    << std::endl;
        }
      } else if (info.filename == "ExportUpgrades_" + lang + ".json") {
        auto er = glz::read<glz::opts{.error_on_missing_keys = true}>(
            exports.upgrades, response.text);
        if (er) {
          std::cout << glz::format_error(er, response.text) << __LINE__
                    << std::endl;
        }
      } else if (info.filename == "ExportWarframes_" + lang + ".json") {
        auto er = glz::read<glz::opts{.error_on_missing_keys = true}>(
            exports.warframes, response.text);
        if (er) {
          std::cout << glz::format_error(er, response.text) << __LINE__
                    << std::endl;
        }
      } else if (info.filename == "ExportWeapons_" + lang + ".json") {
        auto er = glz::read<glz::opts{.error_on_missing_keys = true}>(
            exports.weapons, response.text);
        if (er) {
          std::cout << glz::format_error(er, response.text) << __LINE__
                    << std::endl;
        }
      } else if (info.filename == "ExportManifest_" + lang + ".json") {
        auto er = glz::read<glz::opts{.error_on_missing_keys = true}>(
            exports.manifest, response.text);
        if (er) {
          std::cout << glz::format_error(er, response.text) << __LINE__
                    << std::endl;
        }
      } else {
        throw std::runtime_error("Unknown export data: " + info.filename);
      }
    }
  }
  return *this;
}
