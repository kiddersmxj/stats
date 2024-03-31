cmake_minimum_required(VERSION 3.11)
 
# --- Fetch libs --------------------------------------------------------------

include(FetchContent)
 
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG main
)
 
FetchContent_GetProperties(ftxui)
if(NOT ftxui_POPULATED)
  FetchContent_Populate(ftxui)
  add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

# ------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.11)

project(stats
  LANGUAGES CXX
  VERSION 1.0.0
)

add_executable(stats src/stats.cpp)

find_package(std-k REQUIRED)

target_include_directories(stats
    PRIVATE inc
)

install(
    TARGETS stats
    DESTINATION /usr/local/bin/
)

target_link_libraries(stats
    PRIVATE ftxui::screen
    PRIVATE ftxui::dom
    PRIVATE ftxui::component
    PRIVATE std-k
    PRIVATE nlohmann_json::nlohmann_json
)
target_compile_features(stats PUBLIC cxx_std_20)

target_sources(stats
    PRIVATE src/stats.cpp
    PRIVATE src/display.cpp
    PRIVATE src/graphs.cpp
    PRIVATE src/values.cpp
)

# Copyright (c) 2024, Maxamilian Kidd-May
# All rights reserved.

# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.

