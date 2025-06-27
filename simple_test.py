#!/usr/bin/env python3

import json
import sys
from pathlib import Path

# Simple test configuration
simple_config = {
    "name": "testlib",
    "version": "1.0.0",
    "language": "c",
    "description": "Test library",
    "author": "Test Author",
    "modules": [
        {
            "name": "core",
            "description": "Core module",
            "functions": [
                {
                    "name": "test_func",
                    "return_type": "int",
                    "description": "Test function",
                    "parameters": [
                        {
                            "name": "value",
                            "type": "int",
                            "description": "Input value"
                        }
                    ]
                }
            ]
        }
    ]
}

# Save test config
with open('test_config.json', 'w') as f:
    json.dump(simple_config, f, indent=2)

print("Created simple test configuration")

# Try to import and run generator
try:
    from code_generator import CppCodeGenerator
    
    generator = CppCodeGenerator()
    config = generator.load_config('test_config.json')
    
    print(f"Loaded config for: {config['name']}")
    print(f"Modules: {len(config['modules'])}")
    
    # Try generating
    generator.generate_library(config)
    print("✅ Generation successful!")
    
except Exception as e:
    print(f"❌ Error: {e}")
    import traceback
    traceback.print_exc()
    sys.exit(1)
