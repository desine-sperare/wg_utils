cmake_minimum_required(VERSION 3.5.0)
project(wg_utils VERSION 1.0.0 LANGUAGES CXX)

set(SOURCE_LIB ./src/wg_utils.cpp)

add_library(wg_utils ${SOURCE_LIB})

include_directories(./libs/string_utils/include)
include_directories(./libs/time/include)
include_directories(./include)

add_subdirectory(libs/string_utils)
add_subdirectory(libs/time)

target_link_libraries(wg_utils time)
target_link_libraries(wg_utils string_utils)