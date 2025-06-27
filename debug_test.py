#!/usr/bin/env python3

import json
from code_generator import CppCodeGenerator

# Load the debug config
with open('debug_config.json', 'r') as f:
    config = json.load(f)

generator = CppCodeGenerator()
config = generator.load_config('debug_config.json')

print("Config loaded successfully")
print(f"Module: {config['modules'][0]['name']}")
print(f"Constants: {config['modules'][0].get('constants', [])}")
print(f"Enums: {config['modules'][0].get('enums', [])}")

# Test template rendering step by step
module = config['modules'][0]

# Check each component
print("\nTesting constants iteration:")
if 'constants' in module:
    print(f"Constants type: {type(module['constants'])}")
    for i, const in enumerate(module['constants']):
        print(f"  {i}: {const}")

print("\nTesting enums iteration:")  
if 'enums' in module:
    print(f"Enums type: {type(module['enums'])}")
    for i, enum in enumerate(module['enums']):
        print(f"  {i}: {enum}")

# Now try template rendering
try:
    print("\nTesting template rendering...")
    result = generator.render_template('c/header.h.j2', {'config': config, 'module': module})
    print("✅ Template rendering successful!")
    print("First 200 chars:", result[:200])
except Exception as e:
    print(f"❌ Template error: {e}")
    import traceback
    traceback.print_exc()
