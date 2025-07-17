#include <cpr/cpr.h>
#include <glaze/glaze.hpp>
#include <iostream>
#include <lzma.h>
#include <stdexcept>
#include <vector>

#include "Warframe/API/ManifestIndex.h"

int main(int argc, char *argv[]) {

  ManifestIndex index{};

  for (const auto &[lang, data] : index.language_index) {
    std::cout << "Language: " << lang << " ";
    std::cout << "Filename: " << data.filename << "\n";
    for (const auto &[key, value] : data) {
      const public_export::Info &info = data.*value;
      std::cout << "  " << key << ": " << std::string(info) << "\n";
    }
    // Add more fields as needed
  }
  return 0;
}
