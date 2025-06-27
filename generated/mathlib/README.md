# mathlib

A mathematical computation library with vector operations and statistical functions

**Version:** 1.0.0  
**Language:** C  
**Author:** Code Generator  
**License:** MIT  

## Overview

mathlib is a C library that provides A mathematical computation library with vector operations and statistical functions.

### Key Features

- ✅ **Robust Error Handling**: Comprehensive error reporting and handling mechanisms
- ✅ **Memory Safe**: Proper memory management with leak prevention
- ✅ **Cross-Platform**: Works on Linux, Windows, macOS- ✅ **Well Documented**: Extensive API documentation and examples
- ✅ **Unit Tested**: Comprehensive test suite with unity framework
- ✅ **Modern Standards**: Uses C99 standard

## Table of Contents

- [Installation](#installation)
- [Quick Start](#quick-start)
- [API Reference](#api-reference)
  - [Vector Module](#vector-module)
  - [Stats Module](#stats-module)
- [Examples](#examples)
- [Building from Source](#building-from-source)
- [Testing](#testing)
- [Contributing](#contributing)
- [License](#license)

## Installation

### Using CMake

```cmake
find_package(mathlib REQUIRED)
target_link_libraries(your_target mathlib::mathlib)
```

### Using pkg-config

```bash
gcc `pkg-config --cflags --libs mathlib` your_file.c```

### Manual Installation

```bash
git clone https://github.com/your-username/mathlib.git
cd mathlib
mkdir build && cd build
cmake ..
make install
```

## Quick Start

### C Example

```c
#include <mathlib/vector.h>
#include <stdio.h>

int main() {
    // Initialize the library
    vector_error_t result = vector_init();
    if (result != VECTOR_SUCCESS) {
        fprintf(stderr, "Failed to initialize: %s\n", 
                vector_error_string(result));
        return 1;
    }

    // Use the library
    printf("mathlib v1.0.0 initialized successfully!\n");

    // Cleanup
    result = vector_cleanup();
    if (result != VECTOR_SUCCESS) {
        fprintf(stderr, "Cleanup failed: %s\n", 
                vector_error_string(result));
        return 1;
    }

    return 0;
}
```

### Compilation

```bash
gcc -std=c99 -o example example.c -lmathlib
```

## API Reference


### Vector Module

Vector operations and linear algebra functions

#### Constants

- `VECTOR_MAX_SIZE`: Maximum vector size (1024)
- `VECTOR_DEFAULT_TOLERANCE`: Default floating point tolerance (1e-9)

#### Enumerations

##### Vector_norm

Vector norm types

- `VECTOR_NORM_L1`: L1 norm (Manhattan distance)
- `VECTOR_NORM_L2`: L2 norm (Euclidean distance)
- `VECTOR_NORM_INF`: Infinity norm (maximum element)


#### Structures

##### Vector

Dynamic vector structure

```ctypedef struct vector_s {
    double* data; // Vector data array
    size_t size; // Number of elements
    size_t capacity; // Allocated capacity
} vector_t;
```


#### Functions

##### vector_create

Create a new vector with specified size

```cvector_error_t vector_create(
size_t size,vector_t** vec);
```

**Parameters:**
- `size`: Initial vector size
- `vec`: Output vector pointer

**Returns:** vector_error_t - Error code

**Example:**
```cvector_error_t result = vector_create(size, vec);
if (result != VECTOR_SUCCESS) {
    fprintf(stderr, "Error: %s\n", vector_error_string(result));
}
```

##### vector_destroy

Destroy a vector and free its memory

```cvector_error_t vector_destroy(
vector_t** vec);
```

**Parameters:**
- `vec`: Vector to destroy

**Returns:** vector_error_t - Error code

**Example:**
```cvector_error_t result = vector_destroy(vec);
if (result != VECTOR_SUCCESS) {
    fprintf(stderr, "Error: %s\n", vector_error_string(result));
}
```

##### vector_add

Add two vectors element-wise

```cvector_error_t vector_add(
const vector_t** a,const vector_t** b,vector_t** result);
```

**Parameters:**
- `a`: First vector
- `b`: Second vector
- `result`: Result vector

**Returns:** vector_error_t - Error code

**Example:**
```cvector_error_t result = vector_add(a, b, result);
if (result != VECTOR_SUCCESS) {
    fprintf(stderr, "Error: %s\n", vector_error_string(result));
}
```

##### vector_dot_product

Calculate dot product of two vectors

```cvector_error_t vector_dot_product(
const vector_t** a,const vector_t** b,double** result);
```

**Parameters:**
- `a`: First vector
- `b`: Second vector
- `result`: Output dot product

**Returns:** vector_error_t - Error code

**Example:**
```cvector_error_t result = vector_dot_product(a, b, result);
if (result != VECTOR_SUCCESS) {
    fprintf(stderr, "Error: %s\n", vector_error_string(result));
}
```

##### vector_norm

Calculate vector norm

```cvector_error_t vector_norm(
const vector_t** vec,vector_norm_t norm_type,double** result);
```

**Parameters:**
- `vec`: Input vector
- `norm_type`: Type of norm to calculate
- `result`: Output norm value

**Returns:** vector_error_t - Error code

**Example:**
```cvector_error_t result = vector_norm(vec, norm_type, result);
if (result != VECTOR_SUCCESS) {
    fprintf(stderr, "Error: %s\n", vector_error_string(result));
}
```



### Stats Module

Statistical analysis functions




#### Functions

##### stats_mean

Calculate arithmetic mean of array

```cstats_error_t stats_mean(
const double** data,size_t size,double** result);
```

**Parameters:**
- `data`: Input data array
- `size`: Array size
- `result`: Output mean value

**Returns:** stats_error_t - Error code

**Example:**
```cstats_error_t result = stats_mean(data, size, result);
if (result != STATS_SUCCESS) {
    fprintf(stderr, "Error: %s\n", stats_error_string(result));
}
```

##### stats_variance

Calculate variance of array

```cstats_error_t stats_variance(
const double** data,size_t size,double** result);
```

**Parameters:**
- `data`: Input data array
- `size`: Array size
- `result`: Output variance value

**Returns:** stats_error_t - Error code

**Example:**
```cstats_error_t result = stats_variance(data, size, result);
if (result != STATS_SUCCESS) {
    fprintf(stderr, "Error: %s\n", stats_error_string(result));
}
```

##### stats_correlation

Calculate correlation coefficient between two arrays

```cstats_error_t stats_correlation(
const double** x,const double** y,size_t size,double** result);
```

**Parameters:**
- `x`: First data array
- `y`: Second data array
- `size`: Array size
- `result`: Output correlation coefficient

**Returns:** stats_error_t - Error code

**Example:**
```cstats_error_t result = stats_correlation(x, y, size, result);
if (result != STATS_SUCCESS) {
    fprintf(stderr, "Error: %s\n", stats_error_string(result));
}
```



## Examples

### Complete Examples

Check the `examples/` directory for complete working examples:

- `basic_usage.c` - Basic library usage
- `error_handling.c` - Comprehensive error handling
- `multi_module.c` - Using multiple modules

## Building from Source

### Prerequisites

- C compiler supporting C99 standard (GCC, Clang, MSVC)
- CMake 3.16 or later
- Dependencies:
  - m
### Build Steps

```bash
# Clone the repository
git clone https://github.com/your-username/mathlib.git
cd mathlib

# Create build directory
mkdir build && cd build

# Configure
cmake .. -DCMAKE_BUILD_TYPE=Release

# Build
cmake --build . --parallel

# Install (optional)
sudo cmake --install .
```

### Build Options

- `CMAKE_BUILD_TYPE`: Build type (Debug, Release, RelWithDebInfo, MinSizeRel)
- `MATHLIB_BUILD_TESTS`: Build test suite (default: OFF)
- `BUILD_SHARED_LIBS`: Build shared library instead of static (default: OFF)

## Testing

The library includes a comprehensive test suite using unity.

### Running Tests

```bash
# Build with tests enabled
cmake .. -DMATHLIB_BUILD_TESTS=ON

# Build the tests
cmake --build . --target mathlib_tests

# Run the tests
ctest --output-on-failure
```

### Test Coverage

To generate test coverage reports:

```bash
# Configure with coverage
cmake .. -DMATHLIB_BUILD_TESTS=ON -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_FLAGS="--coverage"

# Build and run tests
cmake --build .
ctest

# Generate coverage report
gcov src/*.clcov --capture --directory . --output-file coverage.info
genhtml coverage.info --output-directory coverage_html
```

## Performance Considerations

- The library is designed for both performance and safety
- Memory allocations are minimized and predictable
- Thread safety is considered in the design

## Platform Support

| Platform | Status | Notes |
|----------|--------|--------|
| Linux    | ✅ Supported | Tested on Ubuntu, CentOS, Alpine |
| Windows  | ✅ Supported | MSVC, MinGW, Clang |
| macOS    | ✅ Supported | Clang, GCC via Homebrew |

## Contributing

We welcome contributions! Please see [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines.

### Development Setup

1. Fork the repository
2. Create a feature branch: `git checkout -b feature/amazing-feature`
3. Make your changes
4. Add tests for new functionality
5. Ensure all tests pass: `cmake --build . && ctest`
6. Commit your changes: `git commit -m 'Add amazing feature'`
7. Push to the branch: `git push origin feature/amazing-feature`
8. Open a Pull Request

### Code Style

- Follow the existing code style
- Use snake_case for function and variable names
- Use UPPER_CASE for constants and macros
- Include comprehensive documentation
- Write unit tests for new functionality

## Troubleshooting

### Common Issues

1. **Compilation errors**: Ensure your compiler supports C992. **Linking errors**: Make sure the library is properly installed and linked
3. **Runtime errors**: Check the error messages using the error string functions

### Getting Help

- Check the [FAQ](FAQ.md)
- Search existing [issues](https://github.com/your-username/mathlib/issues)
- Create a new issue with detailed information

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- Generated using C/C++ Code Generator
- Built with modern C best practices
- Inspired by industry-standard libraries

---

**Generated on:** 2025-06-19  
**Generator Version:** 1.0.0  
**Documentation Version:** 1.0.0