cmake_minimum_required(VERSION 3.20)
project(mxc-test CXX)

find_package(mxc::math CONFIG REQUIRED)

add_executable(package-test src/package_test.cpp)
target_link_libraries(example PRIVATE mxc::math)
