cmake_minimum_required(VERSION 3.8)
project(mathTests)

enable_testing()

# dependencies
find_package(Catch2 3 CONFIG REQUIRED) # find_package has 2 overloads: MODULE (prefer system installed library and 
                                       # search for find script) and CONFIG(look for a package config file)
                                       # default is MODULE, can change with set(CMAKE_FIND_PACKAGE_PREFER_CONFIG ON)
## if you are in the test directory and didn't build the main lib yet, include guard will take care of it 
#if (NOT TARGET mxc::math)
#    set(math_DIR ${CMAKE_CURRENT_BINARY_DIR}/../)
#    find_package(math CONFIG REQUIRED)
#endif()

# Shouldn't be necessary
#if (NOT Catch2_FOUND)
#    message(STATUS "could't find Catch2 library, required to build test suite, attempting to fetch it from github...")
#    include(FetchContent)
#
#    FetchContent_Declare(
#        Catch2
#        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
#        GIT_TAG devel
#    )
#
#    FetchContent_MakeAvailable(Catch2)
#    list(APPEND CMAKE_MODULE_PATH "${Catch2_SOURCE_DIR}/extras")
#    message(STATUS "... fetched Catch2 successfully.")
#endif()

# target definition
add_executable(tests vec.cpp)

# executables with Catch2-provided main
target_link_libraries(tests 
    PRIVATE mxc::math Catch2::Catch2WithMain
)

# TODO: if you need custom tests with their own main, uncomment
#add_executable(custom-main-tests test.cpp test-main.cpp)
#target_link_libraries(custom-main-tests PRIVATE Catch2::Catch2)

include(CTest)
include(Catch)
include(ParseAndAddCatchTests)
catch_discover_tests(tests) # calls add_test for us
