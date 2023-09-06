cmake_minimum_required(VERSION 3.23.2)

# RPATH details
if (NOT APPLE)
    set(CMAKE_INSTALL_RPATH $ORIGIN)
endif()

# library definition
add_library(mxc-core)
target_sources(mxc-core
    PRIVATE
        src/logging.cpp
    INTERFACE
        FILE_SET interface_headers
        TYPE HEADERS
        BASE_DIRS include
        FILES
            include/mcore/logging.h
            include/mcore/macros.h
            include/mcore/memory.h
)

# dependencies (logging uses fmt)
find_package(fmt CONFIG REQUIRED)
target_link_libraries(mxc-core PRIVATE fmt::fmt)
target_compile_features(mxc-core
    PUBLIC cxx_std_20
)

target_include_directories(mxc-core
    PRIVATE
        src
        include/mcore
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# TODO export version and other variables in a config file for easier update
set(core_VERSION 0.0.1)
set_target_properties(mxc-core PROPERTIES
    EXPORT_NAME core
    VERSION ${core_VERSION}
    SOVERSION 0
    INTERFACE_core_MAJOR_VERSION 0
    EXPORT_NAME core
    OUTPUT_NAME mcore
)
set_property(TARGET mxc-core APPEND PROPERTY COMPATIBLE_INTERFACE_STRING core_MAJOR_VERSION)

# TODO compile runtime library too (.so and .dll and what not)

# export library interface
include(GNUInstallDirs)
install(TARGETS mxc-core
    EXPORT coreTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT mcore_Runtime
        NAMELINK_COMPONENT mcore_Development
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT mcore_Development
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        COMPONENT mcore_Runtime
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILE_SET interface_headers DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

set(core_INSTALL_CMAKEDIR
    ${CMAKE_INSTALL_LIBDIR}/cmake/core
    CACHE STRING "Path to mxc::core cmake files"
)

#export target to core_INSTALL_CMAKEDIR
install(EXPORT coreTargets
    DESTINATION ${core_INSTALL_CMAKEDIR}
    FILE coreTargets.cmake
    NAMESPACE mxc::
)

# TODO: remove if creates duplicates
# export to build tree
export(EXPORT coreTargets
    FILE ${CMAKE_CURRENT_BINARY_DIR}/cmake/core/coreTargets.cmake
    NAMESPACE mxc::
)

# create alias with name of the imported target to the original library
add_library(mxc::core ALIAS mxc-core)

include(CMakePackageConfigHelpers)

# generate a config file so that external code knows where to locate package with find_package
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/coreConfig.cmake"
    INSTALL_DESTINATION ${core_INSTALL_CMAKEDIR}
)

# provide info about package version
write_basic_package_version_file(coreConfigVersion.cmake
    VERSION ${core_VERSION}
    COMPATIBILITY SameMajorVersion
)

# TODO: remove if it creates duplicates
#install config and configVersion files
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/coreConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/coreConfigVersion.cmake
    DESTINATION ${core_INSTALL_CMAKEDIR}
)

include(CMakeFindDependencyMacro)
find_dependency(fmt)
