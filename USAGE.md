# C/C++ Code Generator Usage Guide

This guide explains how to use the C/C++ Code Generator to create robust, portable, and well-documented libraries.

## Quick Start

1. **Install dependencies**:
   ```bash
   pip install -r requirements.txt
   ```

2. **Run the test**:
   ```bash
   ./test_generator.sh
   ```

3. **Generate your own library**:
   ```bash
   python code_generator.py --config your_config.json
   ```

## Configuration File Format

The generator uses JSON or YAML configuration files that define your library structure. Here's a complete example:

### Basic Configuration

```json
{
  "name": "mylib",
  "version": "1.0.0",
  "language": "c",
  "description": "My awesome C library",
  "author": "Your Name",
  "license": "MIT"
}
```

### Advanced Configuration

See `examples/mathlib_config.json` and `examples/dataprocessor_config.json` for complete examples.

## Key Features

### 📋 Input Validation
- JSON schema validation for configuration files
- Comprehensive error checking and reporting
- Type safety for all parameters

### 🏗️ Code Generation
- **Headers**: Clean, well-documented header files with proper include guards
- **Sources**: Implementation files with error handling and best practices
- **Build Systems**: CMake, Make, and other build system support
- **Tests**: Comprehensive test suites (Unity, Google Test, Catch2)
- **Documentation**: Professional README files with examples

### 🛡️ Best Practices
- **Error Handling**: Return codes (C) or exceptions (C++) with descriptive messages
- **Memory Management**: Safe allocation/deallocation patterns
- **Thread Safety**: Proper state management and synchronization
- **Portability**: Cross-platform compatible code generation

### 🎯 Language Support

#### C Language Features
- C89/C99/C11/C17/C2x standard support
- Proper error code enums
- Structure definitions with documentation
- Function declarations with parameter validation
- Memory management helpers

#### C++ Language Features  
- C++11/14/17/20/23 standard support
- RAII resource management
- Exception-based error handling
- Modern C++ idioms (smart pointers, move semantics)
- Namespace organization
- Template-friendly design

## Command Line Usage

```bash
python code_generator.py [OPTIONS]

Options:
  -c, --config FILE      Configuration file (JSON or YAML) [required]
  -o, --output DIR       Output directory [default: generated]
  -t, --templates DIR    Templates directory [default: templates]
  -v, --verbose          Enable verbose logging
  --help                 Show help message
```

## Configuration Schema

### Root Level Properties

| Property | Type | Required | Description |
|----------|------|----------|-------------|
| `name` | string | ✅ | Library name (valid C identifier) |
| `version` | string | ✅ | Semantic version (e.g., "1.0.0") |
| `language` | string | ✅ | "c", "cpp", or "c++" |
| `description` | string | ❌ | Library description |
| `author` | string | ❌ | Author name |
| `license` | string | ❌ | License type |
| `modules` | array | ✅ | Library modules |

### Module Properties

| Property | Type | Required | Description |
|----------|------|----------|-------------|
| `name` | string | ✅ | Module name |
| `description` | string | ❌ | Module description |
| `functions` | array | ❌ | Module functions |
| `structures` | array | ❌ | Data structures |
| `enums` | array | ❌ | Enumerations |
| `constants` | array | ❌ | Constants |

### Function Properties

| Property | Type | Required | Description |
|----------|------|----------|-------------|
| `name` | string | ✅ | Function name |
| `return_type` | string | ✅ | Return type |
| `parameters` | array | ❌ | Function parameters |
| `description` | string | ❌ | Function description |
| `is_static` | boolean | ❌ | Static function |
| `is_inline` | boolean | ❌ | Inline function |

## Template Customization

The generator uses Jinja2 templates that you can customize:

### Template Structure
```
templates/
├── c/                    # C language templates
│   ├── header.h.j2
│   └── source.c.j2
├── cpp/                  # C++ language templates  
│   ├── header.h.j2
│   └── source.cpp.j2
├── cmake/                # CMake templates
│   └── CMakeLists.txt.j2
├── make/                 # Makefile templates
│   └── Makefile.j2
├── tests/                # Test templates
│   ├── unity/
│   └── gtest/
└── docs/                 # Documentation templates
    └── README.md.j2
```

### Available Template Variables

- `config`: Full configuration object
- `module`: Current module being processed
- `function`: Current function being processed
- Custom filters: `snake_case`, `pascal_case`, `header_guard`, etc.

### Custom Filters Example

```jinja2
{{ module.name | snake_case }}     <!-- module_name -->
{{ module.name | pascal_case }}    <!-- ModuleName -->
{{ module.name | upper }}          <!-- MODULE_NAME -->
{{ filename | header_guard }}      <!-- FILENAME_H_ -->
```

## Generated Code Structure

```
generated/your_library/
├── CMakeLists.txt           # Build configuration
├── Makefile                 # Alternative build system
├── README.md                # Documentation
├── include/
│   └── your_library/
│       ├── module1.h        # Public headers
│       └── module2.h
├── src/
│   ├── module1.c/.cpp       # Implementation files
│   └── module2.c/.cpp
└── tests/
    ├── test_module1.c/.cpp  # Unit tests
    └── test_module2.c/.cpp
```

## Examples

### Simple C Library

```json
{
  "name": "calculator",
  "version": "1.0.0", 
  "language": "c",
  "modules": [
    {
      "name": "math",
      "functions": [
        {
          "name": "add",
          "return_type": "double",
          "parameters": [
            {"name": "a", "type": "double"},
            {"name": "b", "type": "double"}
          ]
        }
      ]
    }
  ]
}
```

### Modern C++ Library

```json
{
  "name": "network", 
  "version": "2.0.0",
  "language": "cpp",
  "namespace": "net",
  "cpp_standard": "cpp17",
  "modules": [
    {
      "name": "client",
      "functions": [
        {
          "name": "connect",
          "return_type": "void",
          "parameters": [
            {"name": "url", "type": "std::string", "is_const": true}
          ]
        }
      ]
    }
  ]
}
```

## Best Practices

### 1. Configuration Design
- Use descriptive names for modules and functions
- Include comprehensive descriptions
- Define proper error handling strategy
- Specify dependencies explicitly

### 2. Code Organization
- Group related functions into modules
- Use consistent naming conventions
- Define clear data structures
- Include comprehensive constants

### 3. Error Handling
- **C**: Use error code enums with descriptive messages
- **C++**: Use exception hierarchies with detailed information
- Always validate input parameters
- Provide error string conversion functions

### 4. Memory Management
- **C**: Use explicit allocation/deallocation patterns
- **C++**: Prefer RAII and smart pointers
- Check for null pointers
- Avoid memory leaks

### 5. Testing
- Write comprehensive unit tests
- Test error conditions
- Include performance tests
- Validate edge cases

## Troubleshooting

### Common Issues

1. **Template not found**: Check templates directory path
2. **Schema validation failed**: Verify configuration against schema
3. **File generation failed**: Check output directory permissions
4. **Compilation errors**: Review generated code and dependencies

### Debug Mode

Run with `--verbose` for detailed logging:

```bash
python code_generator.py --config config.json --verbose
```

## Contributing

To extend the generator:

1. **Add new templates**: Create template files in appropriate directories
2. **Extend schema**: Update `schemas/library.json` for new features  
3. **Add filters**: Extend `_setup_jinja_filters()` in `code_generator.py`
4. **Add tests**: Create test configurations and verify output

## Advanced Features

### Multi-Language Support
- Generate C libraries with C++ compatibility
- Support for multiple language standards
- Cross-language bindings

### Build System Integration  
- CMake with modern target-based configuration
- Makefile with dependency tracking
- Support for package managers (Conan, vcpkg)

### Documentation Generation
- Professional README files
- API documentation
- Build instructions
- Usage examples

This code generator follows industry best practices and generates production-ready code that you can immediately use in your projects!
