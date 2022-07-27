cmake_minimum_required(VERSION 3.23.2)
project(minmath)

add_library(minmath_lib *sourceslist*)

target_include_directories(minmath_lib "${PROJECT_SOURCE_DIR}/include")