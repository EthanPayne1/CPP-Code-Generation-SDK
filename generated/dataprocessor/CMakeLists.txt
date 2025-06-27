cmake_minimum_required(VERSION 3.16)

# Project configuration
project(dataprocessor
    VERSION 2.1.0
    DESCRIPTION "A modern C++ data processing library with stream processing and analysis capabilities"
    LANGUAGES CXX)

# Set default build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Compiler and language standards
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler-specific options
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
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
        -Wnon-virtual-dtor
        -Wold-style-cast
        -Woverloaded-virtual
        -Wsuggest-override
    )
    
    # Additional flags for different build types
    set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -DDEBUG -fsanitize=address,undefined")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g -DNDEBUG")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
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
set(DATAPROCESSOR_VERSION_MAJOR 2)
set(DATAPROCESSOR_VERSION_MINOR 1)
set(DATAPROCESSOR_VERSION_PATCH 0)

# Source files
set(DATAPROCESSOR_SOURCES
    src/stream.cpp    src/analyzer.cpp)

# Header files
set(DATAPROCESSOR_HEADERS
    include/dataprocessor/stream.h
    include/dataprocessor/analyzer.h
)

# Create library
add_library(dataprocessor ${DATAPROCESSOR_SOURCES} ${DATAPROCESSOR_HEADERS})

# Library properties
set_target_properties(dataprocessor PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 2
    PUBLIC_HEADER "${DATAPROCESSOR_HEADERS}"
)

# Include directories
target_include_directories(dataprocessor
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Dependencies
# Find required packages
find_package(Threads REQUIRED)
target_link_libraries(dataprocessor PUBLIC Threads)
find_package(OpenMP )
target_link_libraries(dataprocessor PRIVATE OpenMP)

# Compiler definitions
target_compile_definitions(dataprocessor
    PRIVATE
        DATAPROCESSOR_VERSION_MAJOR=2
        DATAPROCESSOR_VERSION_MINOR=1
        DATAPROCESSOR_VERSION_PATCH=0
        DATAPROCESSOR_VERSION_STRING="${PROJECT_VERSION}"
)

# Testing
option(DATAPROCESSOR_BUILD_TESTS "Build tests" OFF)

if(DATAPROCESSOR_BUILD_TESTS)
    enable_testing()
    
    # Find test framework
    find_package(GTest REQUIRED)
    
    # Test executable
    file(GLOB_RECURSE TEST_SOURCES tests/*.cpp)
    add_executable(dataprocessor_tests ${TEST_SOURCES})
    
    target_link_libraries(dataprocessor_tests
        PRIVATE
            dataprocessor
            GTest::gtest_main
    )
    
    target_include_directories(dataprocessor_tests
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/include
            ${CMAKE_CURRENT_SOURCE_DIR}/tests
    )
    
    # Add tests to CTest
    include(GoogleTest)
    gtest_discover_tests(dataprocessor_tests)
endif()

# Installation
include(GNUInstallDirs)

install(TARGETS dataprocessor
    EXPORT dataprocessorTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/dataprocessor
)

# Install export targets
install(EXPORT dataprocessorTargets
    FILE dataprocessorTargets.cmake
    NAMESPACE dataprocessor::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/dataprocessor
)

# Create config file
include(CMakePackageConfigHelpers)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/dataprocessorConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/dataprocessorConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/dataprocessor
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/dataprocessorConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/dataprocessorConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/dataprocessorConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/dataprocessor
)

# Package configuration
set(CPACK_PACKAGE_NAME "dataprocessor")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A modern C++ data processing library with stream processing and analysis capabilities")
set(CPACK_PACKAGE_VENDOR "Code Generator Team")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")

include(CPack)

# Show configuration summary
message(STATUS "")
message(STATUS "dataprocessor Configuration Summary:")
message(STATUS "  Version: ${PROJECT_VERSION}")
message(STATUS "  Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "  Install prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "  Build tests: ${DATAPROCESSOR_BUILD_TESTS}")
message(STATUS "")