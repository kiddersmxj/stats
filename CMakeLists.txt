# ──────────────────────────────────────────────────────────────────────────────
#  Top-level configuration
# ──────────────────────────────────────────────────────────────────────────────
cmake_minimum_required(VERSION 3.11)

set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

if(POLICY CMP0135)
  cmake_policy(SET CMP0135 NEW)
endif()

project(
  stats
  LANGUAGES CXX
  VERSION   1.0.0
)

# ──────────────────────────────────────────────────────────────────────────────
#  Third-party dependencies
# ──────────────────────────────────────────────────────────────────────────────
include(FetchContent)
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)

# ---- FTXUI -------------------------------------------------------------------
FetchContent_Declare(
  ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG        main
)
FetchContent_MakeAvailable(ftxui)

# ---- nlohmann/json -----------------------------------------------------------
FetchContent_Declare(
  json
  URL                         https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz
  DOWNLOAD_EXTRACT_TIMESTAMP  TRUE
)
FetchContent_MakeAvailable(json)

# ──────────────────────────────────────────────────────────────────────────────
#  Targets
# ──────────────────────────────────────────────────────────────────────────────
add_executable(stats
  src/stats.cpp
  src/display.cpp
  src/graphs.cpp
  src/values.cpp
)

find_package(std-k REQUIRED)

target_include_directories(stats PRIVATE inc)

target_link_libraries(stats
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component
  PRIVATE std-k
  PRIVATE nlohmann_json::nlohmann_json
)

target_compile_features(stats PUBLIC cxx_std_20)

install(TARGETS stats DESTINATION /usr/local/bin/)

# Copyright (c) 2024, Maxamilian Kidd-May
# All rights reserved.

# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.
