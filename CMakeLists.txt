cmake_minimum_required(VERSION 3.20)
project(WarframeModels LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# FetchContent for Glaze v5.5.2
include(FetchContent)
FetchContent_Declare(
    glaze
    GIT_REPOSITORY https://github.com/stephenberry/glaze.git
    GIT_TAG v5.5.3
)
FetchContent_MakeAvailable(glaze)

# ==== Allow FetchContenting us ====

add_library(warframe_models INTERFACE)
target_include_directories(warframe_models INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)

# ==== Allow Installing us ====

# === Install support ===
include(GNUInstallDirs)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(TARGETS warframe_models EXPORT warframe_modelsTargets)

install(EXPORT warframe_modelsTargets
    FILE warframe_modelsTargets.cmake
    NAMESPACE warframe_models::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/warframe_models
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/warframe_modelsConfigVersion.cmake"
    VERSION 1.0.0
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/warframe_modelsConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/warframe_modelsConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/warframe_models
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/warframe_modelsConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/warframe_modelsConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/warframe_models
)

# ==== Build Example ====

option(BUILD_EXAMPLE "Build example executable" ON)

if (BUILD_EXAMPLE)
    add_executable(example main.cpp)
    target_link_libraries(example PRIVATE warframe_models glaze::glaze)
endif()

# === Download and Copy all.json ===

option(DOWNLOAD_WARFRAME_JSON "Download all.json automatically at configure time" ON)
set(JSON_URL "https://raw.githubusercontent.com/WFCD/warframe-drop-data/gh-pages/data/all.json")
set(JSON_LOCAL_PATH "${CMAKE_BINARY_DIR}/all.json")

if(DOWNLOAD_WARFRAME_JSON)
    file(DOWNLOAD
        ${JSON_URL}
        ${JSON_LOCAL_PATH}
        STATUS download_status
        SHOW_PROGRESS
    )

    list(GET download_status 0 status_code)
    if (NOT status_code EQUAL 0)
        message(FATAL_ERROR "Failed to download all.json from ${JSON_URL}")
    endif()

    # Copy to all 3 desired locations
    file(COPY "${JSON_LOCAL_PATH}" DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}")
    file(COPY "${JSON_LOCAL_PATH}" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
    # Already in CMAKE_BINARY_DIR, so optional

    message(STATUS "all.json downloaded and copied to project directories.")
else()
    message(STATUS "Skipping download of all.json (DOWNLOAD_WARFRAME_JSON=OFF)")
endif()