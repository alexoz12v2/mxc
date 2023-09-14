cmake_minimum_required(VERSION 3.23.2)

# file loaded at the beginning of each subdirectory listing. Basically global variables
# TODO doesn't work
#set(CMAKE_PROJECT_INCLUDE_BEFORE "${CMAKE_CURRENT_LIST_DIR}/common-project-include.cmake.in")
project(mxc
	VERSION 0.0.1
	DESCRIPTION "https://github.com/alexoz12v2/mxc"
	HOMEPAGE_URL "Minimal math library, part of the MXC collection of utilities"
	LANGUAGES C CXX CUDA ASM
)

# project code
add_subdirectory(src/core)
add_subdirectory(src/platform)
add_subdirectory(src/math)

# unit tests
enable_testing()
# add_subdirectory(src/platform/test) TODO
add_subdirectory(src/math/test)
