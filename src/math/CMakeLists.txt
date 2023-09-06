cmake_minimum_required(VERSION 3.23.2)

if (NOT APPLE)
    set(CMAKE_INSTALL_RPATH $ORIGIN)
endif()

# library defini
add_library(mxc-math)
target_sources(mxc-math
    PRIVATE 
        src/common.cpp
    PUBLIC
        FILE_SET public_headers
        TYPE HEADERS
        BASE_DIRS include
        FILES
            include/mmath/common.h
            include/mmath/powlog.h
            include/mmath/constants.h
    INTERFACE
        FILE_SET interface_headers
        TYPE HEADERS
        BASE_DIRS include
        FILES
            include/mmath/number.h
            include/mmath/trig.h
            include/mmath/vec.h
            include/mmath/macros.h
            include/mmath/detail/vec_base.h
            include/mmath/detail/vec_swizzler.h
)

target_compile_features(mxc-math PUBLIC cxx_std_20)

# TODO not needed, specified in file sets
target_include_directories(mxc-math 
    PRIVATE
        src
        include/mmath
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# TODO help me what am I doing
if(NOT TARGET mxc::platform)
    if(NOT TARGET platform)
        find_package(platform CONFIG REQUIRED)
        message(WARNING "there is neither any platform target nor any mxc::platform target")
        set(platform_NOT_EXISTING TRUE)
    else()
        add_library(mxc::platform ALIAS platform)
        set(platform_NOT_EXISTING FALSE)
    endif()
endif()

# dependencies
add_dependencies(mxc-math mxc::platform)

target_link_libraries(mxc-math PUBLIC mxc::platform mxc::core)

# enable disable SIMD TODO config file outside
# TODO: Is a cache variable better than having to define/undefine macros before including the header?
set(math_VECTORIZE CACHE BOOL ON)
if (math_VECTORIZE)
    target_compile_definitions(mxc-math PUBLIC MXC_MATH_VECTORIZE=1)
endif()

set(math_VERSION 0.0.1)
set_target_properties(mxc-math PROPERTIES 
    VERSION ${math_VERSION}
    SOVERSION 0
    INTERFACE_math_MAJOR_VERSION 0
    EXPORT_NAME math 
    OUTPUT_NAME mmath
)
set_property(TARGET mxc-math APPEND PROPERTY COMPATIBLE_INTERFACE_STRING math_MAJOR_VERSION)

# export library interface
include(GNUInstallDirs)
install(TARGETS mxc-math
	EXPORT mathTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            COMPONENT mmath_Runtime
            NAMELINK_COMPONENT mmath_Development
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
            COMPONENT mmath_Development
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
            COMPONENT mmath_Runtime
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        FILE_SET public_headers DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        FILE_SET interface_headers DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# install PUBLIC and INTERFACE files
set(math_INSTALL_CMAKEDIR
    ${CMAKE_INSTALL_LIBDIR}/cmake/math
    CACHE STRING "Path to SomeProj cmake files"
)

#install(FILES 
#            include/mmath/common.h
#            include/mmath/powlog.h
#            include/mmath/constants.h
#            include/mmath/number.h
#            include/mmath/trig.h
#            include/mmath/vec.h
#        DESTINATION ${math_INSTALL_CMAKEDIR}/mmath)

# export to CMAKE_INSTALL_PREFIX
install(EXPORT mathTargets
        DESTINATION lib/cmake/math
        FILE mathTargets.cmake
        NAMESPACE mxc::
        COMPONENT math_Development)

# export to build tree
export(EXPORT mathTargets
       FILE ${CMAKE_CURRENT_BINARY_DIR}/cmake/math/mathTargets.cmake
       NAMESPACE mxc::)

# create an alias target
add_library(mxc::math ALIAS mxc-math)

# copy public headers
#install(DIRECTORY include
#        DESTINATION include)

include(CMakePackageConfigHelpers)

# generate a config file so that external code knows where to locate package with find_package
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/mathConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/math
    PATH_VARS CMAKE_INSTALL_LIBDIR
)

# provide info about package version
write_basic_package_version_file(mathConfigVersion.cmake
    VERSION ${math_VERSION}
    COMPATIBILITY SameMajorVersion)

install(FILES 
            ${CMAKE_CURRENT_BINARY_DIR}/mathConfig.cmake 
            ${CMAKE_CURRENT_BINARY_DIR}/mathConfigVersion.cmake
        DESTINATION lib/cmake/math)

# install target package
if(platform_NOT_EXISTING)
    include(CMakeFindDependencyMacro)
    find_dependency(platform)
endif()
