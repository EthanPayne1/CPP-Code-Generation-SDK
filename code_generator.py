#!/usr/bin/env python3
"""
C/C++ Code Generator
A professional tool for generating robust, portable, and well-documented C/C++ libraries.
"""

import json
import os
import sys
import argparse
import logging
from pathlib import Path
from typing import Dict, List, Any, Optional
from datetime import datetime

import click
from jinja2 import Environment, FileSystemLoader, Template
from jsonschema import validate, ValidationError
import yaml


class CodeGeneratorError(Exception):
    """Custom exception for code generation errors."""
    pass


class CppCodeGenerator:
    """Main code generator class for C/C++ libraries."""
    
    def __init__(self, templates_dir: str = "templates", output_dir: str = "generated"):
        self.templates_dir = Path(templates_dir)
        self.output_dir = Path(output_dir)
        self.schemas_dir = Path("schemas")
        
        # Setup Jinja2 environment
        self.jinja_env = Environment(
            loader=FileSystemLoader(str(self.templates_dir)),
            trim_blocks=True,
            lstrip_blocks=True
        )
        
        # Add custom filters
        self._setup_jinja_filters()
        
        # Setup logging
        logging.basicConfig(
            level=logging.INFO,
            format='%(asctime)s - %(levelname)s - %(message)s'
        )
        self.logger = logging.getLogger(__name__)
    
    def _setup_jinja_filters(self):
        """Setup custom Jinja2 filters."""
        
        def to_upper_case(text: str) -> str:
            return text.upper()
        
        def to_snake_case(text: str) -> str:
            import re
            return re.sub(r'(?<!^)(?=[A-Z])', '_', text).lower()
        
        def to_camel_case(text: str) -> str:
            components = text.split('_')
            return components[0] + ''.join(x.title() for x in components[1:])
        
        def to_pascal_case(text: str) -> str:
            return ''.join(word.title() for word in text.split('_'))
        
        def header_guard(filename: str) -> str:
            """Generate header guard macro name."""
            return filename.upper().replace('.', '_').replace('/', '_') + '_'
        
        self.jinja_env.filters['upper'] = to_upper_case
        self.jinja_env.filters['snake_case'] = to_snake_case
        self.jinja_env.filters['camel_case'] = to_camel_case
        self.jinja_env.filters['pascal_case'] = to_pascal_case
        self.jinja_env.filters['header_guard'] = header_guard
    
    def load_schema(self, schema_name: str) -> Dict[str, Any]:
        """Load JSON schema for validation."""
        schema_path = self.schemas_dir / f"{schema_name}.json"
        if not schema_path.exists():
            raise CodeGeneratorError(f"Schema not found: {schema_path}")
        
        with open(schema_path, 'r') as f:
            return json.load(f)
    
    def validate_config(self, config: Dict[str, Any], schema_name: str = "library") -> None:
        """Validate configuration against schema."""
        try:
            schema = self.load_schema(schema_name)
            validate(instance=config, schema=schema)
            self.logger.info("Configuration validation passed")
        except ValidationError as e:
            raise CodeGeneratorError(f"Configuration validation failed: {e.message}")
        except FileNotFoundError:
            self.logger.warning(f"Schema {schema_name} not found, skipping validation")
    
    def load_config(self, config_path: str) -> Dict[str, Any]:
        """Load configuration from JSON or YAML file."""
        config_file = Path(config_path)
        if not config_file.exists():
            raise CodeGeneratorError(f"Configuration file not found: {config_path}")
        
        with open(config_file, 'r') as f:
            if config_file.suffix.lower() in ['.yaml', '.yml']:
                config = yaml.safe_load(f)
            else:
                config = json.load(f)
        
        # Add metadata
        config['generated_at'] = datetime.now().isoformat()
        config['generator_version'] = "1.0.0"
        
        return config
    
    def render_template(self, template_name: str, context: Dict[str, Any]) -> str:
        """Render a template with given context."""
        try:
            template = self.jinja_env.get_template(template_name)
            return template.render(**context)
        except Exception as e:
            raise CodeGeneratorError(f"Template rendering failed for {template_name}: {str(e)}")
    
    def ensure_output_dir(self, path: Path) -> None:
        """Ensure output directory exists."""
        path.parent.mkdir(parents=True, exist_ok=True)
    
    def write_file(self, content: str, filepath: Path) -> None:
        """Write content to file."""
        self.ensure_output_dir(filepath)
        with open(filepath, 'w') as f:
            f.write(content)
        self.logger.info(f"Generated: {filepath}")
    
    def generate_header(self, config: Dict[str, Any], module: Dict[str, Any]) -> str:
        """Generate C/C++ header file."""
        language = config.get('language', 'c').lower()
        template_name = f"{language}/header.h.j2"
        
        context = {
            'config': config,
            'module': module,
            'include_guard': f"{module['name'].upper()}_H_",
            'namespace': config.get('namespace', ''),
        }
        
        return self.render_template(template_name, context)
    
    def generate_source(self, config: Dict[str, Any], module: Dict[str, Any]) -> str:
        """Generate C/C++ source file."""
        language = config.get('language', 'c').lower()
        extension = 'cpp' if language == 'cpp' else 'c'
        template_name = f"{language}/source.{extension}.j2"
        
        context = {
            'config': config,
            'module': module,
            'header_file': f"{module['name']}.h",
        }
        
        return self.render_template(template_name, context)
    
    def generate_cmake(self, config: Dict[str, Any]) -> str:
        """Generate CMakeLists.txt file."""
        template_name = "cmake/CMakeLists.txt.j2"
        return self.render_template(template_name, {'config': config})
    
    def generate_makefile(self, config: Dict[str, Any]) -> str:
        """Generate Makefile."""
        template_name = "make/Makefile.j2"
        return self.render_template(template_name, {'config': config})
    
    def generate_test(self, config: Dict[str, Any], module: Dict[str, Any]) -> str:
        """Generate test file."""
        language = config.get('language', 'c').lower()
        test_framework = config.get('test_framework', 'unity')
        template_name = f"tests/{test_framework}/{language}_test.j2"
        
        context = {
            'config': config,
            'module': module,
            'test_framework': test_framework,
        }
        
        return self.render_template(template_name, context)
    
    def generate_documentation(self, config: Dict[str, Any]) -> str:
        """Generate README documentation."""
        template_name = "docs/README.md.j2"
        return self.render_template(template_name, {'config': config})
    
    def generate_library(self, config: Dict[str, Any]) -> None:
        """Generate complete library based on configuration."""
        self.logger.info(f"Generating library: {config['name']}")
        
        # Validate configuration
        self.validate_config(config)
        
        # Create output directory structure
        lib_dir = self.output_dir / config['name']
        src_dir = lib_dir / "src"
        include_dir = lib_dir / "include" / config['name']
        test_dir = lib_dir / "tests"
        docs_dir = lib_dir / "docs"
        
        language = config.get('language', 'c').lower()
        source_ext = 'cpp' if language == 'cpp' else 'c'
        
        # Generate modules
        for module in config.get('modules', []):
            # Generate header
            header_content = self.generate_header(config, module)
            header_path = include_dir / f"{module['name']}.h"
            self.write_file(header_content, header_path)
            
            # Generate source
            source_content = self.generate_source(config, module)
            source_path = src_dir / f"{module['name']}.{source_ext}"
            self.write_file(source_content, source_path)
            
            # Generate tests
            if config.get('generate_tests', True):
                test_content = self.generate_test(config, module)
                test_path = test_dir / f"test_{module['name']}.{source_ext}"
                self.write_file(test_content, test_path)
        
        # Generate build files
        if 'cmake' in config.get('build_systems', ['cmake']):
            cmake_content = self.generate_cmake(config)
            self.write_file(cmake_content, lib_dir / "CMakeLists.txt")
        
        if 'make' in config.get('build_systems', []):
            makefile_content = self.generate_makefile(config)
            self.write_file(makefile_content, lib_dir / "Makefile")
        
        # Generate documentation
        if config.get('generate_docs', True):
            readme_content = self.generate_documentation(config)
            self.write_file(readme_content, lib_dir / "README.md")
        
        self.logger.info(f"Library generation completed: {lib_dir}")


@click.command()
@click.option('--config', '-c', required=True, help='Configuration file (JSON or YAML)')
@click.option('--output', '-o', default='generated', help='Output directory')
@click.option('--templates', '-t', default='templates', help='Templates directory')
@click.option('--verbose', '-v', is_flag=True, help='Enable verbose logging')
def main(config: str, output: str, templates: str, verbose: bool):
    """C/C++ Code Generator - Generate robust, portable C/C++ libraries."""
    
    if verbose:
        logging.getLogger().setLevel(logging.DEBUG)
    
    try:
        generator = CppCodeGenerator(templates_dir=templates, output_dir=output)
        config_data = generator.load_config(config)
        generator.generate_library(config_data)
        
        click.echo(f"✅ Successfully generated library: {config_data['name']}")
        click.echo(f"📁 Output directory: {output}/{config_data['name']}")
        
    except CodeGeneratorError as e:
        click.echo(f"❌ Error: {e}", err=True)
        sys.exit(1)
    except Exception as e:
        click.echo(f"❌ Unexpected error: {e}", err=True)
        sys.exit(1)


if __name__ == '__main__':
    main()
