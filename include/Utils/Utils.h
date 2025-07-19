#ifndef UTILS_UTILS_H
#define UTILS_UTILS_H

#include <iostream>
#include <string>
#include <vector>


template <typename T>
void print_vector(const std::vector<T> &vec, const std::string &label = "") {
  if (!label.empty()) {
    std::cout << label << ": ";
  }

  std::cout << "[";
  for (size_t i = 0; i < vec.size(); ++i) {
    std::cout << vec[i];
    if (i + 1 < vec.size())
      std::cout << ", ";
  }
  std::cout << "]\n";
}

#endif // UTILS_UTILS_H