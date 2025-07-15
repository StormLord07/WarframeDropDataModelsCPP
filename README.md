# Warframe Drop Data Models (C++)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![C++23](https://img.shields.io/badge/C%2B%2B-23-blue)](https://en.cppreference.com/w/cpp/23)
[![Build with CMake](https://img.shields.io/badge/build%20system-CMake-informational)](https://cmake.org/)
[![Data Source](https://img.shields.io/badge/data-WFCD%2Fwarframe--drop--data-blue)](https://github.com/WFCD/warframe-drop-data)

This project provides a set of C++23 header-only data models and reflection metadata for introspecting [Warframe](https://warframe.com) drop table data, as provided by [WFCD/warframe-drop-data](https://github.com/WFCD/warframe-drop-data).  
It leverages [Glaze](https://github.com/stephenberry/glaze) for fast and flexible JSON parsing and compile-time reflection.

---

## 🔧 Building the Example

This repository includes a small example that loads and introspects the latest drop table JSON.

To build:

```bash
cmake -S . -B build
cmake --build build
```

or 

```bash
cmake -S . -B build
cd build
cmake --build .
```

or

```bash
cmake . -B build
cd build
make
```

The latter may not work on windows if you use MSVC

---

## 📦 Dependencies

* **C++23** compatable compiler (tested with Clang and MSVC)
* [Glaze](https://github.com/stephenberry/glaze) (example automatically downloads using `FetchContent`)

---

## ⬇️ Install with CMake

This was not tested!

```bash
cmake -B build -S .
cmake --build build
cmake --install build
```

---

## 🔗 Usage via FetchContent 

```cmake
include(FetchContent)
FetchContent_Declare(
    warframe_models
    GIT_REPOSITORY https://github.com/StormLord07/WarframeDropDataModelsCPP.git
    GIT_TAG main
)
FetchContent_MakeAvailable(warframe_models)

target_link_libraries(target PRIVATE warframe_models)
```

---

## 🧪 Optional Example Executable
Disable example by passing this:

```cmake
cmake -DBUILD_EXAMPLE=OFF -B build
cmake --build build
```

---

## 📥 JSON Download

By default, the CMake script downloads the latest drop table file from:

```

[https://raw.githubusercontent.com/WFCD/warframe-drop-data/gh-pages/data/all.json](https://raw.githubusercontent.com/WFCD/warframe-drop-data/gh-pages/data/all.json)

````

You can disable this behavior or override the URL via CMake options:

```bash
cmake -DDOWNLOAD_WARFRAME_JSON=OFF -S . -B build
cmake --build build
````

If disabled, place the file manually at the place from which you'll call the executable:

Or override `JSON_URL` and `JSON_LOCAL_PATH` directly in `CMakeLists.txt`.

```

---

## 📚 What's Included

* Strongly typed data structures for:

  * Relics, Mods, Enemies, Blueprints, Events, Rewards, and more
* Glaze-compatible metadata for parsing and validation
* Recursive structure traversal support (e.g. `.size()`)

---

## 🧪 Example Output

When run, the example outputs statistics like:

* Total number of drop records
* Most common items
* Histograms for drop chances
* (and more depending on implementation)

---

## ⚖ License

MIT

```