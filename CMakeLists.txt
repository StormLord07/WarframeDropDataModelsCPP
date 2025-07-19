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

# libcpr
FetchContent_Declare(
    cpr 
    GIT_REPOSITORY https://github.com/libcpr/cpr.git
    GIT_TAG 1.11.0
) 
FetchContent_MakeAvailable(cpr)

FetchContent_Declare(
  liblzma
  URL https://tukaani.org/xz/xz-5.4.5.tar.gz
)

FetchContent_MakeAvailable(liblzma)

include_directories(${xz_SOURCE_DIR}/src/liblzma/api/)

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
    target_link_libraries(example PRIVATE warframe_models glaze::glaze )
endif()

add_executable(api_explorer api_explorer.cpp source/Warframe/API/ManifestIndex.cpp source/Warframe/API/Client.cpp)

function(copy_runtime_dll target lib_target)
    add_custom_command(TARGET ${target} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:${lib_target}>
            $<TARGET_FILE_DIR:${target}>
        COMMENT "Copying runtime DLL from ${lib_target} to ${target}"
    )
endfunction()

copy_runtime_dll(api_explorer cpr::cpr)
# copy_runtime_dll(api_explorer glaze::glaze)  # if it ever becomes shared
copy_runtime_dll(api_explorer liblzma)       # if linked as a target
# copy_runtime_dll(api_explorer zlib::zlib)    # if available
copy_runtime_dll(api_explorer CURL::libcurl) # if found via find_package or fetchcontent

target_link_libraries(api_explorer PRIVATE warframe_models glaze::glaze cpr::cpr liblzma)
target_include_directories(api_explorer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

