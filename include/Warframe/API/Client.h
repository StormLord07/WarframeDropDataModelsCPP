#ifndef WARFRAME_API_CLIENT_H
#define WARFRAME_API_CLIENT_H

#include <cpr/cpr.h>
#include <string>
#include <vector>

#include "Utils/FixedKeyMap.h"
#include "Warframe/API/ManifestIndex.h"
#include "Warframe/Manifest.h"

#include <glaze/glaze.hpp>

class WarframeApiClient {
public:
  explicit WarframeApiClient(std::initializer_list<std::string> languages = {
                                 "de", "en", "es", "fr", "it", "ja", "ko", "pl",
                                 "pt", "ru", "tc", "th", "tr", "uk", "zh"});

  ManifestIndex &getManifestIndex();
  WarframeApiClient &get();

private:
  ManifestIndex manifest_index_;
  FixedKeyUMap<std::string, Exports> language_manifest_;

  static const std::string base_url_;
  cpr::Session session_;
};

#endif // WARFRAME_API_CLIENT_H