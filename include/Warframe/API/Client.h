#ifndef WARFRAME_API_CLIENT_H
#define WARFRAME_API_CLIENT_H

#include <cpr/cpr.h>
#include <string>
#include <vector>

#include "Warfame/API/ManifestIndex.h"

class WarframeApiClient {
public:
  explicit WarframeApiClient(std::string language = "en");

  ManifestIndex getManifestIndex(); // From index.lzma
  std::string downloadManifestFile(const std::string &name);

private:
  ManifestIndex manifest_index_;
  std::string base_url_;
  std::string lang_;
  cpr::Session session_;
};

#endif WARFRAME_API_CLIENT_H