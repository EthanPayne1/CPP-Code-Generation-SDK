cmake_minimum_required(VERSION 3.16)

# Project configuration
project(debuglib
    VERSION 1.0.0
    DESCRIPTION "Debug library"
    LANGUAGES C)

# Set default build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Compiler and language standards
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Compiler-specific options
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(
        -Wall
        -Wextra
        -Wpedantic
        -Wconversion
        -Wsign-conversion
        -Wcast-qual
        -Wformat=2
        -Wundef
        -Wshadow
        -Wcast-align
        -Wunused
        -Wnull-dereference
        -Wdouble-promotion
        -Wimplicit-fallthrough
    )
    
    # Additional flags for different build types
    set(CMAKE_C_FLAGS_DEBUG "-g -O0 -DDEBUG -fsanitize=address,undefined")
    set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG")
    set(CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g -DNDEBUG")
elseif(CMAKE_C_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/W4 /permissive-)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options(/Od /Zi)
        add_compile_definitions(DEBUG)
    else()
        add_compile_options(/O2)
        add_compile_definitions(NDEBUG)
    endif()
endif()

# Platform-specific definitions
if(WIN32)
    add_compile_definitions(
        WIN32_LEAN_AND_MEAN
        NOMINMAX
        _CRT_SECURE_NO_WARNINGS
    )
endif()

# Library configuration
set(DEBUGLIB_VERSION_MAJOR 1)
set(DEBUGLIB_VERSION_MINOR 0)
set(DEBUGLIB_VERSION_PATCH 0)

# Source files
set(DEBUGLIB_SOURCES
    src/debug.c)

# Header files
set(DEBUGLIB_HEADERS
    include/debuglib/debug.h
)

# Create library
add_library(debuglib ${DEBUGLIB_SOURCES} ${DEBUGLIB_HEADERS})

# Library properties
set_target_properties(debuglib PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER "${DEBUGLIB_HEADERS}"
)

# Include directories
target_include_directories(debuglib
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Dependencies

# Compiler definitions
target_compile_definitions(debuglib
    PRIVATE
        DEBUGLIB_VERSION_MAJOR=1
        DEBUGLIB_VERSION_MINOR=0
        DEBUGLIB_VERSION_PATCH=0
        DEBUGLIB_VERSION_STRING="${PROJECT_VERSION}"
)

# Testing

# Installation
include(GNUInstallDirs)

install(TARGETS debuglib
    EXPORT debuglibTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/debuglib
)

# Install export targets
install(EXPORT debuglibTargets
    FILE debuglibTargets.cmake
    NAMESPACE debuglib::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/debuglib
)

# Create config file
include(CMakePackageConfigHelpers)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/debuglibConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/debuglibConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/debuglib
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/debuglibConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/debuglibConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/debuglibConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/debuglib
)

# Package configuration
set(CPACK_PACKAGE_NAME "debuglib")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Debug library")
set(CPACK_PACKAGE_VENDOR "Test")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")

include(CPack)

# Show configuration summary
message(STATUS "")
message(STATUS "debuglib Configuration Summary:")
message(STATUS "  Version: ${PROJECT_VERSION}")
message(STATUS "  Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  C standard: ${CMAKE_C_STANDARD}")
message(STATUS "  Install prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "")