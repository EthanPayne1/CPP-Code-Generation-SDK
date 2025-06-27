cmake_minimum_required(VERSION 3.16)

# Project configuration
project(testlib
    VERSION 1.0.0
    DESCRIPTION "Test library"
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
set(TESTLIB_VERSION_MAJOR 1)
set(TESTLIB_VERSION_MINOR 0)
set(TESTLIB_VERSION_PATCH 0)

# Source files
set(TESTLIB_SOURCES
    src/core.c)

# Header files
set(TESTLIB_HEADERS
    include/testlib/core.h
)

# Create library
add_library(testlib ${TESTLIB_SOURCES} ${TESTLIB_HEADERS})

# Library properties
set_target_properties(testlib PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER "${TESTLIB_HEADERS}"
)

# Include directories
target_include_directories(testlib
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Dependencies

# Compiler definitions
target_compile_definitions(testlib
    PRIVATE
        TESTLIB_VERSION_MAJOR=1
        TESTLIB_VERSION_MINOR=0
        TESTLIB_VERSION_PATCH=0
        TESTLIB_VERSION_STRING="${PROJECT_VERSION}"
)

# Testing

# Installation
include(GNUInstallDirs)

install(TARGETS testlib
    EXPORT testlibTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/testlib
)

# Install export targets
install(EXPORT testlibTargets
    FILE testlibTargets.cmake
    NAMESPACE testlib::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/testlib
)

# Create config file
include(CMakePackageConfigHelpers)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/testlibConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/testlibConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/testlib
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/testlibConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/testlibConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/testlibConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/testlib
)

# Package configuration
set(CPACK_PACKAGE_NAME "testlib")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Test library")
set(CPACK_PACKAGE_VENDOR "Test Author")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")

include(CPack)

# Show configuration summary
message(STATUS "")
message(STATUS "testlib Configuration Summary:")
message(STATUS "  Version: ${PROJECT_VERSION}")
message(STATUS "  Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  C standard: ${CMAKE_C_STANDARD}")
message(STATUS "  Install prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "")