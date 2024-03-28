cmake_minimum_required(VERSION 3.11)
 
# --- Fetch libs --------------------------------------------------------------
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
    PRIVATE std-k
)
target_compile_features(stats PUBLIC cxx_std_20)

# Copyright (c) 2024, Maxamilian Kidd-May
# All rights reserved.

# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.

