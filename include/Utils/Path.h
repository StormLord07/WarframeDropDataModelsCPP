#ifndef UTILS_PATH_H
#define UTILS_PATH_H

#include "Utils/Error.h"

#include <expected>
#include <filesystem>

#if defined(_WIN32)
#include <windows.h>
#else
#include <limits.h>
#include <unistd.h>
#endif

namespace utils {

inline std::expected<std::filesystem::path, ExpectedErrorType>
get_executable_path() {
#if defined(_WIN32)
  char buffer[MAX_PATH];
  DWORD length = GetModuleFileNameA(nullptr, buffer, MAX_PATH);
  if (length == 0 || length == MAX_PATH)
    return std::unexpected("GetModuleFileNameA failed" + (length == MAX_PATH)
                               ? " (buffer too small)"
                               : "(length is zero)");
  return std::filesystem::path(buffer, buffer + length);
#else
  char buffer[PATH_MAX];
  ssize_t length = readlink("/proc/self/exe", buffer, sizeof(buffer));
  if (length == -1)
    return std::unexpected("readlink /proc/self/exe failed");
  return std::filesystem::path(buffer, buffer + length);
#endif
}

inline std::expected<std::filesystem::path, ExpectedErrorType>
get_executable_dir() {
  auto path_or_error = get_executable_path();
  if (!path_or_error)
    return std::unexpected(path_or_error.error());

  return path_or_error->parent_path();
}

} // namespace utils

#endif // UTILS_PATH_H