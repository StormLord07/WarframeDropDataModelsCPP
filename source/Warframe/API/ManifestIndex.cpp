#include "Warframe/API/ManifestIndex.h"

inline std::expected<public_export::Data, std::string>
public_export::Data::parse(const std::vector<std::string> &data) {

  if (data.size() < 12) {
    return std::unexpected(
        "Invalid public export data size: less than 12 entries");
  }

  Data result;

  // Dispatch table: string prefix → member pointer
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
      return std::unexpected("Invalid entry (missing '!'): " + entry);
    }

    std::string_view key = std::string_view(entry).substr(0, pos);
    std::string_view value = std::string_view(entry).substr(pos + 1);

    auto it = std::find_if(table.begin(), table.end(), [&](const auto &pair) {
      return key.starts_with(pair.first);
    });

    if (it == table.end()) {
      return std::unexpected("Unknown public export key: " + std::string(key));
    }

    Info &target = result.*(it->second);
    target.filename = std::string(key);
    target.hash = std::string(value);
  }

  return result;
}

const std::string ManifestIndex::base_url_ =
    "https://content.warframe.com/PublicExport/";

ManifestIndex::ManifestIndex(std::initializer_list<std::string> languages)
    : language_index(languages) {}

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
    if (!line.empty() && line.back() == '\r')
      line.pop_back();
    decompressed_strings.push_back(std::move(line));
  }
  return decompressed_strings;
}

std::expected<public_export::Data, ExpectedErrorType>
ManifestIndex::get(std::string language) {
  std::string filename = "index_" + language + ".txt.lzma";
  this->session_.SetOption(cpr::Url{this->base_url_ + filename});
  auto response = this->session_.Get();
  if (response.status_code != 200) {
    return std::unexpected(ExpectedErrorType(
        "Failed to download manifest index for " + language + " status code: " +
        std::to_string(response.status_code) + " message: " + response.reason));
  }
  auto decompressed_data = this->lzma24_decompress(response.text);
  auto data = public_export::Data::parse(decompressed_data);
  if (!data) {
    return data;
  }
  data.value().filename =
      filename.substr(0, filename.size() - 5); // Remove ".lzma"
  return data;
}

std::expected<void, ExpectedErrorType> ManifestIndex::get() {
  for (const auto &[language, value] : this->language_index) {
    auto result = this->get(language);
    if (!result) {
      return std::unexpected(result.error());
    }
    this->language_index[language] = result.value();
  }
  return {};
}

std::expected<void, ExpectedErrorType>
ManifestIndex::save(std::string_view data, const std::filesystem::path &path) {
  std::ofstream file(path);
  if (!file.is_open()) {
    return std::unexpected("Failed to open file: " + path.string());
  }

  file.write(data.data(), data.size());
  if (!file.good()) {
    return std::unexpected("Failed to write data to file: " + path.string());
  }

  return {};
}

std::expected<void, ExpectedErrorType> ManifestIndex::save() {
  std::filesystem::path manifest_dir = "./Manifest";
  std::filesystem::path compressed_dir = manifest_dir / "Compressed";

  std::error_code ec;
  std::filesystem::create_directories(manifest_dir, ec);
  if (ec) {
    return std::unexpected("Failed to create manifest_dir: " + ec.message());
  }

  for (const auto &[language, data] : this->language_index) {
    std::filesystem::path uncompressed_path = manifest_dir / data.filename;
    std::string plain_data = std::string(data); // Convert to string
    if (auto res = save(plain_data, uncompressed_path); !res) {
      return res;
    }
  }
  return {};
}

std::expected<public_export::Data, ExpectedErrorType>
ManifestIndex::load(const std::filesystem::path &path) {
  if (!std::filesystem::exists(path)) {
    return std::unexpected("File does not exist: " + path.string());
  }

  std::ifstream file(path);
  if (!file.is_open()) {
    return std::unexpected("Failed to open file: " + path.string());
  }

  std::vector<std::string> lines;
  std::string line;
  while (std::getline(file, line)) {
    lines.push_back(std::move(line));
  }

  print_vector(lines, "Loaded lines");

  auto data = public_export::Data::parse(lines);
  if (!data) {
    return data;
  }

  data.value().filename = path.filename().string();
  return data.value();
}

std::expected<void, ExpectedErrorType> ManifestIndex::load() {
  std::filesystem::path manifest_dir = "./Manifest";
  if (!std::filesystem::exists(manifest_dir)) {
    return std::unexpected("Manifest directory does not exist: " +
                           manifest_dir.string());
  }

  for (auto &[language, _] : this->language_index) {
    if (language.size() != 2 ||
        !std::all_of(language.begin(), language.end(),
                     [](char c) { return c >= 'a' && c <= 'z'; })) {
      return std::unexpected("Invalid language key in index: " + language);
    }

    std::string filename = "index_" + language + ".txt";
    std::filesystem::path full_path = manifest_dir / filename;

    auto result = this->load(full_path);
    if (!result) {
      return std::unexpected(result.error());
    }

    this->language_index[language] = result.value();
  }

  return {};
}

std::expected<void, ExpectedErrorType> ManifestIndex::tryLoad() {
  std::filesystem::path manifest_dir = "./Manifest";
  if (!std::filesystem::exists(manifest_dir)) {
    return this->get();
  }

  for (auto &[language, _] : this->language_index) {
    std::string filename = "index_" + language + ".txt";
    std::filesystem::path full_path = manifest_dir / filename;

    auto load_result = this->load(full_path);
    if (load_result) {
      this->language_index[language] = load_result.value();
      continue;
    }
    // Fallback to downloading
    auto get_result = this->get(language);
    if (!get_result) {
      return std::unexpected("Failed to load or fetch manifest for language" +
                             language + " :\n" +
                             " Load error : " + load_result.error() + "\n " +
                             "Fetch error: " + get_result.error());
    }

    this->language_index[language] = get_result.value();
  }

  return {};
}
