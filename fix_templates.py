#!/usr/bin/env python3

import os
import re

# Template files to fix
template_files = [
    "templates/c/header.h.j2",
    "templates/cpp/header.h.j2", 
    "templates/cpp/source.cpp.j2",
    "templates/tests/gtest/cpp_test.j2",
    "templates/docs/README.md.j2"
]

def fix_template_file(filepath):
    """Fix builtin method conflicts in template file"""
    print(f"Fixing {filepath}...")
    
    with open(filepath, 'r') as f:
        content = f.read()
    
    # Fix enum.values -> enum['values']
    content = re.sub(r'enum\.values', r"enum['values']", content)
    
    # Fix struct.fields -> struct['fields'] 
    content = re.sub(r'struct\.fields', r"struct['fields']", content)
    
    # Fix func.parameters -> func['parameters']
    content = re.sub(r'func\.parameters', r"func['parameters']", content)
    
    with open(filepath, 'w') as f:
        f.write(content)
    
    print(f"  Fixed {filepath}")

# Fix all template files
for template_file in template_files:
    if os.path.exists(template_file):
        fix_template_file(template_file)
    else:
        print(f"Warning: {template_file} not found")

print("All template fixes applied!")
