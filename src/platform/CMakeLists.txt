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

######################################################
# Target Configuration
######################################################
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
    INTERFACE
        FILE_SET interface_headers
        TYPE HEADERS
        BASE_DIRS include
        FILES
            include/mplatform/simd.h
            include/mplatform/cpu.generated.h
)

# dependencies (TODO uncomment when needed)
# find_package(mxc::core CONFIG REQUIRED)
# target_link_libraries(PRIVATE mxc::core)
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
        FILE_SET interface_headers DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}) 

# install PUBLIC and INTERFACE files
set(platform_INSTALL_CMAKEDIR
    ${CMAKE_INSTALL_LIBDIR}/cmake/platform
    CACHE STRING "Path to SomeProj cmake files"
)

#install(FILES 
#            include/mplatform/cpu.generated.h
#            include/mplatform/simd.h
#        DESTINATION ${platform_INSTALL_CMAKEDIR}/mplatform)

# export to CMAKE_INSTALL_PREFIX
install(EXPORT platformTargets
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/platform
        NAMESPACE mxc::
        FILE platformTargets.cmake
        COMPONENT platform_Development)

# export to the build tree
export(EXPORT platformTargets
       FILE ${CMAKE_CURRENT_BINARY_DIR}/cmake/platform/platformTargets.cmake
       NAMESPACE mxc::)

# Create an IMPORTED Target, NOT AN ALIAS?
#add_library(mxc::platform STATIC IMPORTED)
#set_target_properties(mxc::platform PROPERTIES
#    INTERFACE_INCLUDE_DIRECTORIES ${_IMPORT_PREFIX}/include
#)
# Set imported target as global
#set_target_properties(mxc::platform PROPERTIES IMPORTED_GLOBAL TRUE)

# alias 
add_library(mxc::platform ALIAS mxc-platform)

# copy public headers
#install(DIRECTORY include
#        DESTINATION include)

include(CMakePackageConfigHelpers)

# generate a config file so that external code knows where to locate package with find_package
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/platformConfig.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/platform
)

# provide info about package version
write_basic_package_version_file(platformConfigVersion.cmake
    VERSION ${platform_VERSION}
    COMPATIBILITY AnyNewerVersion)

# install config and configversion files
install(FILES
          ${CMAKE_CURRENT_BINARY_DIR}/platformConfig.cmake
          ${CMAKE_CURRENT_BINARY_DIR}/platformConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/platform)

# install target package (TODO uncomment when needed)
 # include(CMakeFindDependencyMacro) 
 # find_dependency(mxc::core)
