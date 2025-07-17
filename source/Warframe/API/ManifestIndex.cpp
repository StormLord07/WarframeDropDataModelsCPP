#include "Warframe/API/ManifestIndex.h"

inline public_export::Data
public_export::Data::parse(const std::vector<std::string> &data) {
  if (data.size() < 12) {
    throw std::runtime_error("Invalid public export data size");
  }

  Data result;

  // Type alias to reduce noise
  using InfoPtr = std::string public_export::Data::*;

  // Dispatch table: string prefix -> member pointer
  static const std::unordered_map<std::string_view, Info public_export::Data::*>
      table{
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

  for (const auto &entry : data) {
    auto pos = entry.find('!');
    if (pos == std::string::npos) {
      throw std::runtime_error("Invalid entry (missing '!'): " + entry);
    }

    std::string_view key = std::string_view(entry).substr(0, pos);
    std::string_view value = std::string_view(entry).substr(pos + 1);

    auto it = std::find_if(table.begin(), table.end(), [&](const auto &pair) {
      return key.starts_with(pair.first);
    });

    if (it == table.end()) {
      throw std::runtime_error("Unknown public export key: " +
                               std::string(key));
    }

    Info &target = result.*(it->second);
    target.filename = std::string(key);
    target.hash = std::string(value);
  }

  return result;
}

ManifestIndex::ManifestIndex(std::initializer_list<std::string> languages)
    : language_index(languages) {
  static const std::string base_url =
      "https://content.warframe.com/PublicExport/";
  for (const auto &[language, value] : this->language_index) {
    std::string filename = "index_" + language + ".txt.lzma";
    this->session_.SetOption(cpr::Url{base_url + filename});
    auto response = this->session_.Get();
    if (response.status_code != 200) {
      throw std::runtime_error("Failed to download manifest index for " +
                               language);
    }
    auto decompressed_data = this->lzma24_decompress(response.text);
    auto data = public_export::Data::parse(decompressed_data);
    data.filename = filename;
    this->language_index[language] = data;
  }
}

std::vector<std::string>
ManifestIndex::lzma24_decompress(const std::string_view data) {
  lzma_stream strm = LZMA_STREAM_INIT;
  if (lzma_auto_decoder(&strm, UINT64_MAX, 0) != LZMA_OK) {
    throw std::runtime_error("Failed to initialize LZMA decoder");
  }

  // Skip 24-byte header
  strm.next_in = (uint8_t *)data.data();
  strm.avail_in = data.size();

  std::vector<uint8_t> output(10 * 1024 * 1024); // 10MB buffer
  strm.next_out = output.data();
  strm.avail_out = output.size();

  if (lzma_code(&strm, LZMA_FINISH) != LZMA_STREAM_END) {
    lzma_end(&strm);
    throw std::runtime_error("LZMA decompression failed");
  }

  output.resize(output.size() - strm.avail_out);
  lzma_end(&strm);

  std::vector<std::string> decompressed_strings;

  std::string decompressed_str(output.begin(), output.end());

  std::istringstream stream(decompressed_str);
  std::string line;
  while (std::getline(stream, line)) {
    decompressed_strings.push_back(line);
  }
  return decompressed_strings;
}