cmake_minimum_required(VERSION 3.16)

# Project configuration
project(mathlib
    VERSION 1.0.0
    DESCRIPTION "A mathematical computation library with vector operations and statistical functions"
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
set(MATHLIB_VERSION_MAJOR 1)
set(MATHLIB_VERSION_MINOR 0)
set(MATHLIB_VERSION_PATCH 0)

# Source files
set(MATHLIB_SOURCES
    src/vector.c    src/stats.c)

# Header files
set(MATHLIB_HEADERS
    include/mathlib/vector.h
    include/mathlib/stats.h
)

# Create library
add_library(mathlib ${MATHLIB_SOURCES} ${MATHLIB_HEADERS})

# Library properties
set_target_properties(mathlib PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER "${MATHLIB_HEADERS}"
)

# Include directories
target_include_directories(mathlib
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Dependencies
# Find required packages

# Compiler definitions
target_compile_definitions(mathlib
    PRIVATE
        MATHLIB_VERSION_MAJOR=1
        MATHLIB_VERSION_MINOR=0
        MATHLIB_VERSION_PATCH=0
        MATHLIB_VERSION_STRING="${PROJECT_VERSION}"
)

# Testing
option(MATHLIB_BUILD_TESTS "Build tests" OFF)

if(MATHLIB_BUILD_TESTS)
    enable_testing()
    
    # Find test framework
    # Unity is typically included as source
    add_subdirectory(extern/unity EXCLUDE_FROM_ALL)
    
    # Test executable
    file(GLOB_RECURSE TEST_SOURCES tests/*.c)
    add_executable(mathlib_tests ${TEST_SOURCES})
    
    target_link_libraries(mathlib_tests
        PRIVATE
            mathlib
            unity
    )
    
    target_include_directories(mathlib_tests
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/include
            ${CMAKE_CURRENT_SOURCE_DIR}/tests
    )
    
    # Add tests to CTest
    add_test(NAME mathlib_tests COMMAND mathlib_tests)
endif()

# Installation
include(GNUInstallDirs)

install(TARGETS mathlib
    EXPORT mathlibTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/mathlib
)

# Install export targets
install(EXPORT mathlibTargets
    FILE mathlibTargets.cmake
    NAMESPACE mathlib::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/mathlib
)

# Create config file
include(CMakePackageConfigHelpers)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/mathlibConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/mathlibConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/mathlib
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/mathlibConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/mathlibConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/mathlibConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/mathlib
)

# Package configuration
set(CPACK_PACKAGE_NAME "mathlib")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A mathematical computation library with vector operations and statistical functions")
set(CPACK_PACKAGE_VENDOR "Code Generator")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")

include(CPack)

# Show configuration summary
message(STATUS "")
message(STATUS "mathlib Configuration Summary:")
message(STATUS "  Version: ${PROJECT_VERSION}")
message(STATUS "  Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  C standard: ${CMAKE_C_STANDARD}")
message(STATUS "  Install prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "  Build tests: ${MATHLIB_BUILD_TESTS}")
message(STATUS "")