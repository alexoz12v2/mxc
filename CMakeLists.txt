cmake_minimum_required(VERSION 3.23.2)
project(minmath)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	add_compile_definitions(_DEBUG)
endif()

add_library(minmath_lib STATIC  
	"src/common.cpp"
	"src/fnumber.cpp"
	"src/fpowlog.cpp"
	"src/ftrig.cpp")

target_include_directories(minmath_lib PUBLIC 
		"${PROJECT_SOURCE_DIR}/include"
		"${PROJECT_SOURCE_DIR}/src")

if(WIN32)
	add_compile_definitions(_HAS_EXCEPTIONS=0)
    if(NOT DEFINED _DEBUG)
        target_compile_options(minmath_lib PRIVATE /std:c++20 /O2 /W4 /GR- /EHsc) 
    else()
        target_compile_options(minmath_lib PRIVATE /std:c++20 /O0 /W4 /DEBUG /Z7 /GR- /EHsc)
    endif()
else()
    # Set the C and C++ compilers to Clang
    set(CMAKE_C_COMPILER "/usr/bin/clang")
    set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
    if(NOT DEFINED _DEBUG)
        target_compile_options(minmath_lib PRIVATE -std=c++20 -O2 -Wall -Wextra -Wpedantic -Werror -fno-rtti -fno-exceptions)
    else()
        target_compile_options(minmath_lib PRIVATE -std=c++20 -O0 -Wall -Wextra -Wpedantic -g -Werror -fno-rtti -fno-exceptions)
    endif()
endif()
