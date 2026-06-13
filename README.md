<div align="center">
  <h1>Raytracer</h1>
  <p><strong>A 3D rendering engine built from scratch in C++</strong></p>
</div>

## Overview

This Raytracer is a custom 3D rendering engine that mathematically simulates the physical behavior of light. By shooting rays from a virtual camera into a mathematical scene definition, it calculates exact light paths, shadows, reflections, and refractions to generate photorealistic images.

## Features

- **Mathematical Rendering:** Calculates perfect sphere, plane, and cylinder intersections.
- **Advanced Lighting:** Supports ambient, diffuse, specular lighting, and hard/soft shadows.
- **Material Properties:** Supports glass (refraction), mirrors (reflection), and matte textures.
- **Scene Parsing:** Reads scenes from configuration files to dynamically build 3D worlds.
- **Multithreading:** Utilizes multiple CPU threads for faster image generation.

## Installation

The project uses CMake for easy configuration and compilation.

```bash
# Generate build files
cmake -B build

# Compile the raytracer
cmake --build build
```

## Creating Your Own Scene

The engine uses `libconfig` `.cfg` files to define scenes. You can create your own custom 3D environments by defining materials, shapes, and lighting!

Create a `my_scene.cfg` file with the following structure:

```cfg
renderer: { resolution = { width = 800; height = 600; }; samples = 10; maxDepth = 5; };
camera:   { position = { x = 0.0; y = 0.0; z = -3.0; }; };

materials: {
    lambertians = ( { name = "red"; color = { r = 255; g = 0; b = 0; }; } );
};

primitives: {
    spheres = ( { position = { x = 0.0; y = 0.0; z = 0.0; }; r = 1.0; material = "red"; } );
};

lights: {
    ambient = 0.5;
};
```

## How to Run

Pass a scene configuration file to the raytracer to generate an image.

```bash
# Example: Render a specific scene from the scenes folder
./raytracer scenes/mirror.cfg
```

The output will be generated as a high-resolution image file (typically `.ppm` or `.png`), which you can open to see the results of the computation!
