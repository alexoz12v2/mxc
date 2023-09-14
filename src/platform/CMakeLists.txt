cmake_minimum_required(VERSION 3.23.2)

######################################################
# Generate CPU Information
######################################################
#message(STATUS "mxc::platform: Generating CPU information")
#message(WARNING "\tDO NOT USE THIS <mplatform/cpu.generated.h> header, as this reports feature support for host architecture, not target")

file(REMOVE ${CMAKE_CURRENT_SOURCE_DIR}/include/mplatform/cpu.generated.h)

add_executable(cpuinfo)

target_sources(cpuinfo PRIVATE
    src/x86_64/cpufeatures.h
    src/x86_64/cpufeatures.cpp
    cmd/generateCPUInformation.cpp
)

target_include_directories(cpuinfo PRIVATE
    include
    src
)

add_custom_command(
    OUTPUT ./include/mplatform/cpu.generated.h
    DEPENDS cmd/generateCPUInformation.cpp
    COMMAND cpuinfo > ${CMAKE_CURRENT_SOURCE_DIR}/include/mplatform/cpu.generated.h
)

# how to add object files to a target: create an object target, set private compiler option,
# see object libraries: https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#object-libraries
# add_library(archiveExtras STATIC $<TARGET_OBJECTS:archive> extras.cpp)

######################################################################################################################
# Compile all simd translation units with different architecture compiler flags
######################################################################################################################
# TODO for now assume x86_64
set(platform_ARCH "x86_64")
message(WARNING "The current approach compiles multiple translation units containing one line functions that forward arguments to appropriate "
                 "compiler intrinsics. This means that the compiler cannot inline such function calls, resulting in an increased cost to the already "
                 "not free dynamic dispatch based on the target CPU's instruction set feature support. There are 2 possible solutions without "
                 "rethinking the whole simd system:\n\t1) Enable Link-Time Optimizations and pray\n\t2) Instead of wrapping intrinsics 1:1, implement "
                 "higher level operations to amortize the call cost")
add_library(avx        OBJECT)
add_library(avx2       OBJECT)
add_library(avx512bw   OBJECT)
add_library(avx512cd   OBJECT)
add_library(avx512dq   OBJECT)
add_library(avx512f    OBJECT)
add_library(avx512vl   OBJECT)
add_library(bmi1       OBJECT)
add_library(f16c       OBJECT)
add_library(fma3       OBJECT)
add_library(popcnt     OBJECT)
add_library(sse        OBJECT)
add_library(sse2       OBJECT)
add_library(sse3       OBJECT)
add_library(sse4_1     OBJECT)
add_library(sse4_2     OBJECT)
add_library(ssse3      OBJECT)
add_library(sse_vex    OBJECT)
add_library(sse2_vex   OBJECT)
add_library(sse3_vex   OBJECT)
add_library(sse4_1_vex OBJECT)
add_library(sse4_2_vex OBJECT)
add_library(ssse3_vex  OBJECT)

target_sources(avx        PRIVATE src/x86_64/extensions/avx.cpp)
target_sources(avx2       PRIVATE src/x86_64/extensions/avx2.cpp)
target_sources(avx512bw   PRIVATE src/x86_64/extensions/avx512bw.cpp)
target_sources(avx512cd   PRIVATE src/x86_64/extensions/avx512cd.cpp)
target_sources(avx512dq   PRIVATE src/x86_64/extensions/avx512dq.cpp)
target_sources(avx512f    PRIVATE src/x86_64/extensions/avx512f.cpp)
target_sources(avx512vl   PRIVATE src/x86_64/extensions/avx512vl.cpp)
target_sources(bmi1       PRIVATE src/x86_64/extensions/bmi1.cpp)
target_sources(f16c       PRIVATE src/x86_64/extensions/f16c.cpp)
target_sources(fma3       PRIVATE src/x86_64/extensions/fma3.cpp)
target_sources(popcnt     PRIVATE src/x86_64/extensions/popcnt.cpp)
target_sources(sse        PRIVATE src/x86_64/extensions/sse.cpp)
target_sources(sse2       PRIVATE src/x86_64/extensions/sse2.cpp)
target_sources(sse3       PRIVATE src/x86_64/extensions/sse3.cpp)
target_sources(sse4_1     PRIVATE src/x86_64/extensions/sse4_1.cpp)
target_sources(sse4_2     PRIVATE src/x86_64/extensions/sse4_2.cpp)
target_sources(ssse3      PRIVATE src/x86_64/extensions/ssse3.cpp)
target_sources(sse_vex    PRIVATE src/x86_64/extensions/sse.cpp)
target_sources(sse2_vex   PRIVATE src/x86_64/extensions/sse2.cpp)
target_sources(sse3_vex   PRIVATE src/x86_64/extensions/sse3.cpp)
target_sources(sse4_1_vex PRIVATE src/x86_64/extensions/sse4_1.cpp)
target_sources(sse4_2_vex PRIVATE src/x86_64/extensions/sse4_2.cpp)
target_sources(ssse3_vex  PRIVATE src/x86_64/extensions/ssse3.cpp)

#
# - any newer revision of a given instruction set implies the presence of all the older ones
# - avx implies sse4.1, sse4.2 and popcnt
# - avx2 implies bmi1 and bmi2 (not reported (yet)), with one exception: "AMD Zen 2 and earlier (in the Zen family) have unusably slow pdep/pext"
# - not all avx2 hardware has fma3
#
# source: https://stackoverflow.com/questions/76428057/do-all-cpus-that-support-avx2-also-support-bmi2-or-popcnt
#
# To be as safe as possible, all instruction set extensions "auxiliary" to SIMD extensions are checked independently, and composed together with
# different translation units containing functions which forward all their arguments to the relevant intrinsic
# exceptions to these rules will be due to msvc /arch insufficient granularity, and are reported with a comment
#
if ((CMAKE_CXX_COMPILER_ID STREQUAL "GNU") OR (CMAKE_CXX_COMPILER_ID STREQUAL "Clang"))
    # do not sett -ffast-math, as we want full IEEE compliance. The aforementioned option enables the following
    #   -fno-math-errno, -funsafe-math-optimizations, -ffinite-math-only, -fno-rounding-math,
    #   -fno-signaling-nans, -fcx-limited-range and -fexcess-precision=fast
    # we need only a subset of these
    #
    # -fno-math-errno, -fno-trapping-math (a part of unsafe optimizations), -fno-signaling-nans (default), -fno-fp-int-builtin-inexact
    # -frename-registers
    set(avx_COMPILE_OPTIONS        "-mavx;-mfpmath=sse;-fno-math-errno;-fno-signaling-nans;-fno-fp-int-builtin-inexact;-fno-trapping-math;-mno-push-args;-msse2avx")
    set(avx2_COMPILE_OPTIONS       "-mavx2;-mfpmath=sse;-fno-math-errno;-fno-signaling-nans;-fno-fp-int-builtin-inexact;-fno-trapping-math;-mno-push-args;-msse2avx")
    set(avx512bw_COMPILE_OPTIONS   "-mavx512bw;-mfpmath=sse;-fno-math-errno;-fno-signaling-nans;-fno-fp-int-builtin-inexact;-fno-trapping-math;-mno-push-args;-msse2avx")
    set(avx512cd_COMPILE_OPTIONS   "-mavx512cd;-mfpmath=sse;-fno-math-errno;-fno-signaling-nans;-fno-fp-int-builtin-inexact;-fno-trapping-math;-mno-push-args;-msse2avx")
    set(avx512dq_COMPILE_OPTIONS   "-mavx512dq;-mfpmath=sse;-fno-math-errno;-fno-signaling-nans;-fno-fp-int-builtin-inexact;-fno-trapping-math;-mno-push-args;-msse2avx")
    set(avx512f_COMPILE_OPTIONS    "-mavx512f;-mfpmath=sse;-fno-math-errno;-fno-signaling-nans;-fno-fp-int-builtin-inexact;-fno-trapping-math;-mno-push-args;-msse2avx")
    set(avx512vl_COMPILE_OPTIONS   "-mavx512vl;-mfpmath=sse;-fno-math-errno;-fno-signaling-nans;-fno-fp-int-builtin-inexact;-fno-trapping-math;-mno-push-args;-msse2avx")
    set(bmi1_COMPILE_OPTIONS       "-mbmi;-mfpmath=sse;-fno-math-errno;-fno-signaling-nans;-fno-fp-int-builtin-inexact;-fno-trapping-math;-mno-push-args")
    set(f16c_COMPILE_OPTIONS       "-mf16c;-mavx;-mfpmath=sse;-fno-math-errno;-fno-signaling-nans;-fno-fp-int-builtin-inexact;-fno-trapping-math;-mno-push-args;-msse2avx")
    set(fma3_COMPILE_OPTIONS       "-mfma;-mavx;-mfpmath=sse;-fno-math-errno;-fno-signaling-nans;-fno-fp-int-builtin-inexact;-fno-trapping-math;-mno-push-args;-msse2avx")
    set(popcnt_COMPILE_OPTIONS     "-mpopcnt;-mfpmath=sse;-fno-math-errno;-fno-signaling-nans;-fno-fp-int-builtin-inexact;-fno-trapping-math;-mno-push-args")
    set(sse2_COMPILE_OPTIONS       "-msse;-mfpmath=sse;-fno-math-errno;-fno-signaling-nans;-fno-fp-int-builtin-inexact;-fno-trapping-math;-mno-push-args;-mno-sse2avx")
    set(sse2_COMPILE_OPTIONS       "-msse;-msse2;-mfpmath=sse;-fno-math-errno;-fno-signaling-nans;-fno-fp-int-builtin-inexact;-fno-trapping-math;-mno-push-args;-mno-sse2avx")
    set(sse3_COMPILE_OPTIONS       "-msse3;-mfpmath=sse;-fno-math-errno;-fno-signaling-nans;-fno-fp-int-builtin-inexact;-fno-trapping-math;-mno-push-args;-mno-sse2avx")
    set(sse4_1_COMPILE_OPTIONS     "-msse4.1;-mfpmath=sse;-fno-math-errno;-fno-signaling-nans;-fno-fp-int-builtin-inexact;-fno-trapping-math;-mno-push-args;-mno-sse2avx")
    set(sse4_2_COMPILE_OPTIONS     "-msse4.2;-mfpmath=sse;-fno-math-errno;-fno-signaling-nans;-fno-fp-int-builtin-inexact;-fno-trapping-math;-mno-push-args;-mno-sse2avx")
    set(ssse3_COMPILE_OPTIONS      "-msse3;-mssse3;-mfpmath=sse;-fno-math-errno;-fno-signaling-nans;-fno-fp-int-builtin-inexact;-fno-trapping-math;-mno-push-args;-mno-sse2avx")
    set(sse_vex_COMPILE_OPTIONS    "-msse;-mfpmath=sse;-fno-math-errno;-fno-signaling-nans;-fno-fp-int-builtin-inexact;-fno-trapping-math;-mno-push-args;-msse2avx")
    set(sse2_vex_COMPILE_OPTIONS   "-msse;-msse2;-mfpmath=sse;-fno-math-errno;-fno-signaling-nans;-fno-fp-int-builtin-inexact;-fno-trapping-math;-mno-push-args;-msse2avx")
    set(sse3_vex_COMPILE_OPTIONS   "-msse3;-mfpmath=sse;-fno-math-errno;-fno-signaling-nans;-fno-fp-int-builtin-inexact;-fno-trapping-math;-mno-push-args;-msse2avx")
    set(sse4_1_vex_COMPILE_OPTIONS "-msse4.1;-mfpmath=sse;-fno-math-errno;-fno-signaling-nans;-fno-fp-int-builtin-inexact;-fno-trapping-math;-mno-push-args;-msse2avx")
    set(sse4_2_vex_COMPILE_OPTIONS "-msse4.2;-mfpmath=sse;-fno-math-errno;-fno-signaling-nans;-fno-fp-int-builtin-inexact;-fno-trapping-math;-mno-push-args;-msse2avx")
    set(ssse3_vex_COMPILE_OPTIONS  "-msse3;-mssse3;-mfpmath=sse;-fno-math-errno;-fno-signaling-nans;-fno-fp-int-builtin-inexact;-fno-trapping-math;-mno-push-args;-msse2avx")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # for floating point behaviour, there aren't many options to tweak for speed while maintaining almost full IEEE compliance, so disable floating
    # point exceptions
    set(avx_COMPILE_OPTIONS        "/arch:AVX;/fp:strict;/fp:except-;fpcvt:IA")
    set(avx2_COMPILE_OPTIONS       "/arch:AVX2/fp:strict;/fp:except-;fpcvt:IA") # note: implies FMA and (a subset of) BMI
    set(avx512bw_COMPILE_OPTIONS   "/arch:AVX512/fp:strict;/fp:except-;fpcvt:IA")
    set(avx512cd_COMPILE_OPTIONS   "/arch:AVX512/fp:strict;/fp:except-;fpcvt:IA")
    set(avx512dq_COMPILE_OPTIONS   "/arch:AVX512/fp:strict;/fp:except-;fpcvt:IA")
    set(avx512f_COMPILE_OPTIONS    "/arch:AVX512/fp:strict;/fp:except-;fpcvt:IA")
    set(avx512vl_COMPILE_OPTIONS   "/arch:AVX512/fp:strict;/fp:except-;fpcvt:IA")
    set(bmi1_COMPILE_OPTIONS       "/arch:AVX2/fp:strict;/fp:except-;fpcvt:IA")
    set(f16c_COMPILE_OPTIONS       "/arch:AVX2/fp:strict;/fp:except-;fpcvt:IA") # note: i found no way to check for these two
    set(fma3_COMPILE_OPTIONS       "/arch:AVX2/fp:strict;/fp:except-;fpcvt:IA") #       so it might not be ideal
    set(popcnt_COMPILE_OPTIONS     "/arch:AVX/fp:strict;/fp:except-;fpcvt:IA")
    set(sse_COMPILE_OPTIONS        "/fp:strict;/fp:except-;fpcvt:IA")
    set(sse2_COMPILE_OPTIONS       "/fp:strict;/fp:except-;fpcvt:IA")
    set(sse3_COMPILE_OPTIONS       "/fp:strict;/fp:except-;fpcvt:IA")
    set(sse4_1_COMPILE_OPTIONS     "/fp:strict;/fp:except-;fpcvt:IA")
    set(sse4_2_COMPILE_OPTIONS     "/fp:strict;/fp:except-;fpcvt:IA")
    set(ssse3_COMPILE_OPTIONS      "/fp:strict;/fp:except-;fpcvt:IA")
    set(sse_vex_COMPILE_OPTIONS    "/arch:AVX/fp:strict;/fp:except-;fpcvt:IA")
    set(sse2_vex_COMPILE_OPTIONS   "/arch:AVX/fp:strict;/fp:except-;fpcvt:IA")
    set(sse3_vex_COMPILE_OPTIONS   "/arch:AVX/fp:strict;/fp:except-;fpcvt:IA")
    set(sse4_1_vex_COMPILE_OPTIONS "/arch:AVX/fp:strict;/fp:except-;fpcvt:IA")
    set(sse4_2_vex_COMPILE_OPTIONS "/arch:AVX/fp:strict;/fp:except-;fpcvt:IA")
    set(ssse3_vex_COMPILE_OPTIONS  "/arch:AVX/fp:strict;/fp:except-;fpcvt:IA")
else ()
    message(FATAL_ERROR "Compiler not supported")
endif ()

target_include_directories(avx        PRIVATE include include/mplatform include/mplatform/x86_64/extensions)
target_include_directories(avx2       PRIVATE include include/mplatform include/mplatform/x86_64/extensions)
target_include_directories(avx512bw   PRIVATE include include/mplatform include/mplatform/x86_64/extensions)
target_include_directories(avx512cd   PRIVATE include include/mplatform include/mplatform/x86_64/extensions)
target_include_directories(avx512dq   PRIVATE include include/mplatform include/mplatform/x86_64/extensions)
target_include_directories(avx512f    PRIVATE include include/mplatform include/mplatform/x86_64/extensions)
target_include_directories(avx512vl   PRIVATE include include/mplatform include/mplatform/x86_64/extensions)
target_include_directories(bmi1       PRIVATE include include/mplatform include/mplatform/x86_64/extensions)
target_include_directories(f16c       PRIVATE include include/mplatform include/mplatform/x86_64/extensions)
target_include_directories(fma3       PRIVATE include include/mplatform include/mplatform/x86_64/extensions)
target_include_directories(popcnt     PRIVATE include include/mplatform include/mplatform/x86_64/extensions)
target_include_directories(sse        PRIVATE include include/mplatform include/mplatform/x86_64/extensions)
target_include_directories(sse2       PRIVATE include include/mplatform include/mplatform/x86_64/extensions)
target_include_directories(sse3       PRIVATE include include/mplatform include/mplatform/x86_64/extensions)
target_include_directories(ssse3      PRIVATE include include/mplatform include/mplatform/x86_64/extensions)
target_include_directories(sse4_1     PRIVATE include include/mplatform include/mplatform/x86_64/extensions)
target_include_directories(sse4_2     PRIVATE include include/mplatform include/mplatform/x86_64/extensions)
target_include_directories(sse_vex    PRIVATE include include/mplatform include/mplatform/x86_64/extensions)
target_include_directories(sse2_vex   PRIVATE include include/mplatform include/mplatform/x86_64/extensions)
target_include_directories(sse3_vex   PRIVATE include include/mplatform include/mplatform/x86_64/extensions)
target_include_directories(ssse3_vex  PRIVATE include include/mplatform include/mplatform/x86_64/extensions)
target_include_directories(sse4_1_vex PRIVATE include include/mplatform include/mplatform/x86_64/extensions)
target_include_directories(sse4_2_vex PRIVATE include include/mplatform include/mplatform/x86_64/extensions)

target_link_libraries(avx        PUBLIC mxc::core)
target_link_libraries(avx2       PUBLIC mxc::core)
target_link_libraries(avx512bw   PUBLIC mxc::core)
target_link_libraries(avx512cd   PUBLIC mxc::core)
target_link_libraries(avx512dq   PUBLIC mxc::core)
target_link_libraries(avx512f    PUBLIC mxc::core)
target_link_libraries(avx512vl   PUBLIC mxc::core)
target_link_libraries(bmi1       PUBLIC mxc::core)
target_link_libraries(f16c       PUBLIC mxc::core)
target_link_libraries(fma3       PUBLIC mxc::core)
target_link_libraries(popcnt     PUBLIC mxc::core)
target_link_libraries(sse        PUBLIC mxc::core)
target_link_libraries(sse2       PUBLIC mxc::core)
target_link_libraries(sse3       PUBLIC mxc::core)
target_link_libraries(ssse3      PUBLIC mxc::core)
target_link_libraries(sse4_1     PUBLIC mxc::core)
target_link_libraries(sse4_2     PUBLIC mxc::core)
target_link_libraries(sse_vex    PUBLIC mxc::core)
target_link_libraries(sse2_vex   PUBLIC mxc::core)
target_link_libraries(sse3_vex   PUBLIC mxc::core)
target_link_libraries(ssse3_vex  PUBLIC mxc::core)
target_link_libraries(sse4_1_vex PUBLIC mxc::core)
target_link_libraries(sse4_2_vex PUBLIC mxc::core)

target_compile_options(avx        PRIVATE ${avx_COMPILE_OPTIONS})
target_compile_options(avx2       PRIVATE ${avx2_COMPILE_OPTIONS})
target_compile_options(avx512bw   PRIVATE ${avx512bw_COMPILE_OPTIONS})
target_compile_options(avx512cd   PRIVATE ${avx512cd_COMPILE_OPTIONS})
target_compile_options(avx512dq   PRIVATE ${avx512dq_COMPILE_OPTIONS})
target_compile_options(avx512f    PRIVATE ${avx512f_COMPILE_OPTIONS})
target_compile_options(avx512vl   PRIVATE ${avx512vl_COMPILE_OPTIONS})
target_compile_options(bmi1       PRIVATE ${bmi1_COMPILE_OPTIONS})
target_compile_options(f16c       PRIVATE ${f16c_COMPILE_OPTIONS})
target_compile_options(fma3       PRIVATE ${fma3_COMPILE_OPTIONS})
target_compile_options(popcnt     PRIVATE ${popcnt_COMPILE_OPTIONS})
target_compile_options(sse        PRIVATE ${sse_COMPILE_OPTIONS})
target_compile_options(sse2       PRIVATE ${sse2_COMPILE_OPTIONS})
target_compile_options(sse3       PRIVATE ${sse3_COMPILE_OPTIONS})
target_compile_options(ssse3      PRIVATE ${ssse3_COMPILE_OPTIONS})
target_compile_options(sse4_1     PRIVATE ${sse4_1_COMPILE_OPTIONS})
target_compile_options(sse4_2     PRIVATE ${sse4_2_COMPILE_OPTIONS})
target_compile_options(sse_vex    PRIVATE ${sse_vex_COMPILE_OPTIONS})
target_compile_options(sse2_vex   PRIVATE ${sse2_vex_COMPILE_OPTIONS})
target_compile_options(sse3_vex   PRIVATE ${sse3_vex_COMPILE_OPTIONS})
target_compile_options(ssse3_vex  PRIVATE ${ssse3_vex_COMPILE_OPTIONS})
target_compile_options(sse4_1_vex PRIVATE ${sse4_1_vex_COMPILE_OPTIONS})
target_compile_options(sse4_2_vex PRIVATE ${sse4_2_vex_COMPILE_OPTIONS})

# MXC_SSE_AS_AVX used to choose the name of the containing C++ namespace (eg sse2:: vs sse2vex::)
target_compile_definitions(sse_vex    PRIVATE MXC_SSE_AS_AVX=1)
target_compile_definitions(sse2_vex   PRIVATE MXC_SSE_AS_AVX=1)
target_compile_definitions(sse3_vex   PRIVATE MXC_SSE_AS_AVX=1)
target_compile_definitions(ssse3_vex  PRIVATE MXC_SSE_AS_AVX=1)
target_compile_definitions(sse4_1_vex PRIVATE MXC_SSE_AS_AVX=1)
target_compile_definitions(sse4_2_vex PRIVATE MXC_SSE_AS_AVX=1)

######################################################################################################################
# Target Configuration
######################################################################################################################
# setting install RPATH details
if (NOT APPLE)
    set(CMAKE_INSTALL_RPATH $ORIGIN)
endif()

add_library(mxc-platform)
target_sources(mxc-platform
    PRIVATE
        src/x86_64/cpufeatures.cpp
        src/x86_64/cpufeatures.h
        include/mplatform/cpu.generated.h
        $<TARGET_OBJECTS:avx>
        $<TARGET_OBJECTS:avx2>
        $<TARGET_OBJECTS:avx512bw>
        $<TARGET_OBJECTS:avx512cd>
        $<TARGET_OBJECTS:avx512dq>
        $<TARGET_OBJECTS:avx512f>
        $<TARGET_OBJECTS:avx512vl>
        $<TARGET_OBJECTS:bmi1>
        $<TARGET_OBJECTS:f16c>
        $<TARGET_OBJECTS:fma3>
        $<TARGET_OBJECTS:popcnt>
        $<TARGET_OBJECTS:sse>
        $<TARGET_OBJECTS:sse2>
        $<TARGET_OBJECTS:sse3>
        $<TARGET_OBJECTS:sse4_1>
        $<TARGET_OBJECTS:sse4_2>
        $<TARGET_OBJECTS:ssse3>
        $<TARGET_OBJECTS:sse_vex>
        $<TARGET_OBJECTS:sse2_vex>
        $<TARGET_OBJECTS:sse3_vex>
        $<TARGET_OBJECTS:sse4_1_vex>
        $<TARGET_OBJECTS:sse4_2_vex>
        $<TARGET_OBJECTS:ssse3_vex>
    INTERFACE
        FILE_SET interface_headers
        TYPE HEADERS
        BASE_DIRS include
        FILES
            include/mplatform/simd.h
            include/mplatform/simd_dispatch.h
            include/mplatform/cpu.generated.h # TODO cpu.generated.h won't work on a target environment different than the build environment
    PUBLIC
        FILE_SET public_headers
        TYPE HEADERS
        BASE_DIRS include
        FILES
            include/mplatform/arch_macros.h
            # TODO x86_64 assumed
            include/mplatform/x86_64/extensions
            include/mplatform/x86_64/extensions/avx.h
            include/mplatform/x86_64/extensions/avx2.h
            include/mplatform/x86_64/extensions/avx512bw.h
            include/mplatform/x86_64/extensions/avx512cd.h
            include/mplatform/x86_64/extensions/avx512dq.h
            include/mplatform/x86_64/extensions/avx512f.h
            include/mplatform/x86_64/extensions/avx512vl.h
            include/mplatform/x86_64/extensions/bmi1.h
            include/mplatform/x86_64/extensions/common_types.h
            include/mplatform/x86_64/extensions/f16c.h
            include/mplatform/x86_64/extensions/fma3.h
            include/mplatform/x86_64/extensions/popcnt.h
            include/mplatform/x86_64/extensions/sse.h
            include/mplatform/x86_64/extensions/sse2.h
            include/mplatform/x86_64/extensions/sse3.h
            include/mplatform/x86_64/extensions/ssse3.h
            include/mplatform/x86_64/extensions/sse4_1.h
            include/mplatform/x86_64/extensions/sse4_2.h
            include/mplatform/x86_64/extensions/ssevex.h
            include/mplatform/x86_64/extensions/sse2vex.h
            include/mplatform/x86_64/extensions/sse3vex.h
            include/mplatform/x86_64/extensions/ssse3vex.h
            include/mplatform/x86_64/extensions/sse4_1vex.h
            include/mplatform/x86_64/extensions/sse4_2vex.h
)

# dependencies
# find_package(mxc::core CONFIG REQUIRED)
add_dependencies(mxc-platform mxc::core)
target_link_libraries(mxc-platform PRIVATE mxc::core)

# how to set public/interface compiler options (not needed, present for future reference)
# https://stackoverflow.com/questions/23995019/what-is-the-modern-method-for-setting-general-compile-flags-in-cmake
# target_compile_options(foo PUBLIC "$<$<CONFIG:DEBUG>:${MY_DEBUG_OPTIONS}>")

target_compile_features(mxc-platform
    PUBLIC cxx_std_20               # public headers features
)

# TODO not needed, specified in file sets
target_include_directories(mxc-platform
    PRIVATE
        src
        include/mplatform
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

set(platform_VERSION 0.0.1)
set_target_properties(mxc-platform PROPERTIES
    EXPORT_NAME platform
    VERSION ${platform_VERSION}
    SOVERSION 0
    INTERFACE_platform_MAJOR_VERSION 0
    EXPORT_NAME platform
    OUTPUT_NAME mplatform
)
set_property(TARGET mxc-platform APPEND PROPERTY COMPATIBLE_INTERFACE_STRING platform_MAJOR_VERSION)

# export library interface
include(GNUInstallDirs)
install(TARGETS mxc-platform
	EXPORT platformTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            COMPONENT mplatform_Runtime
            NAMELINK_COMPONENT mplatform_Development
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
            COMPONENT mplatform_Development
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
            COMPONENT mplatform_Runtime
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        FILE_SET interface_headers DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        FILE_SET public_headers DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# install PUBLIC and INTERFACE files
set(platform_INSTALL_CMAKEDIR
    ${CMAKE_INSTALL_LIBDIR}/cmake/platform
    CACHE STRING "Path to mxc::platform cmake files"
)

# export to CMAKE_INSTALL_PREFIX
install(EXPORT platformTargets
        DESTINATION ${platform_INSTALL_CMAKEDIR}
        NAMESPACE mxc::
        FILE platformTargets.cmake
        COMPONENT platform_Development)

# export to the build tree
export(EXPORT platformTargets
       FILE ${CMAKE_CURRENT_BINARY_DIR}/cmake/platform/platformTargets.cmake
       NAMESPACE mxc::)

# alias
add_library(mxc::platform ALIAS mxc-platform)

include(CMakePackageConfigHelpers)

# generate a config file so that external code knows where to locate package with find_package
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/platformConfig.cmake"
  INSTALL_DESTINATION ${platform_INSTALL_CMAKEDIR}
)

# provide info about package version
write_basic_package_version_file(platformConfigVersion.cmake
    VERSION ${platform_VERSION}
    COMPATIBILITY SameMajorVersion)

# install config and configversion files
install(FILES
          ${CMAKE_CURRENT_BINARY_DIR}/platformConfig.cmake
          ${CMAKE_CURRENT_BINARY_DIR}/platformConfigVersion.cmake
        DESTINATION ${platform_INSTALL_CMAKEDIR})

# install target package (TODO uncomment when needed)
 # include(CMakeFindDependencyMacro)
 # find_dependency(mxc::core)
