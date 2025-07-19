#include <cpr/cpr.h>
#include <glaze/glaze.hpp>
#include <iostream>
#include <lzma.h>
#include <stdexcept>
#include <vector>

#include "Utils/Error.h"
#include "Utils/Path.h"
#include "Warframe/API/Client.h"
#include "Warframe/API/ManifestIndex.h"

#if defined(_WIN32)
#include <windows.h>
#else
#include <limits.h>
#include <unistd.h>

#endif

int main(int argc, char *argv[]) {

  auto dir = utils::get_executable_dir();
  if (!dir) {
    std::cerr << "Error: " << dir.error() << "\n";
    return 1;
  }

#if defined(_WIN32)
  SetCurrentDirectoryA(dir->string().c_str());
#else
  if (chdir(dir->string().c_str()) != 0) {
    std::cerr << "Error changing directory: " << strerror(errno) << "\n";
    return 1;
  }
#endif

  // ManifestIndex index{{"en"}};

  // index.tryLoad();
  // index.save();

  WarframeApiClient client{};
  client.get();

  // for (const auto &[lang, data] : index.language_index) {
  //   std::cout << "Language: " << lang << " ";
  //   std::cout << "Filename: " << data.filename << "\n";
  //   for (const auto &[key, value] : data) {
  //     const public_export::Info &info = data.*value;
  //     std::cout << "  " << key << ": " << std::string(info) << "\n";
  //   }
  //   // Add more fields as needed
  // }
  return 0;
}
