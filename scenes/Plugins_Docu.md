# Raytracer Plugins Documentation

This document lists all the available parameters for each plugin (Primitives and Lights) of your Raytracer rendering engine, as well as the expected syntax in a `.cfg` configuration file.

---

## 1. Global Setup (Camera & Renderer)

Before defining primitives and materials, the `.cfg` file must contain mandatory sections for the `camera` and `renderer` settings.

### 1.1. Camera (`camera`)

The camera block defines the viewpoint from which the scene is rendered.

**Parameters:**

- `position` *(block)*: The 3D coordinates of the camera `{x=..., y=..., z=...}`. *(Optional, default: `{x=0, y=0, z=0}`)*
- `rotation` *(block)*: Euler rotation of the camera in degrees `{x=..., y=..., z=...}`. *(Optional, default: `{x=0, y=0, z=0}`)*
- `fieldOfView` *(float)*: The vertical Field of View (FOV) in degrees. *(Optional, default: 90.0)*

**Example:**

```cfg
camera = {
    position = { x = 0.0; y = 0.0; z = 0.0; }; # Optional
    rotation = { x = 0.0; y = 0.0; z = 0.0; }; # Optional
    fieldOfView = 70.0; # Optional
};
```

### 1.2. Renderer (`renderer`)

The renderer block sets up the global rendering engine parameters.

**Parameters:**

- `resolution` *(block)*: The dimensions of the output image `{width=..., height=...}`. **(Required)**
- `samples` *(int)*: The number of rays to cast per pixel (anti-aliasing and soft shadows). A higher value reduces noise but increases render time. *(Optional, default: 50)*
- `maxDepth` *(int)*: The maximum number of bounces a ray can make (for reflections/refractions). *(Optional, default: 10)*
- `background` *(string)*: Name of the material to use as the background/skybox when a ray hits nothing. *(Optional, default: none/black)*

**Example:**

```cfg
renderer = {
    resolution = { width = 1920; height = 1080; };
    samples = 100; # Optional
    maxDepth = 15; # Optional
    background = "sky_material"; # Optional (Needs to be defined in materials)
};
```

---

## 2. Common Parameters (Standardized)

To simplify scene creation, **all** primitives now use this unified parameter base:

- `position` *(block)*: Object coordinates `{x=..., y=..., z=...}`. **(Required for Sphere, Plane, Cylinder)**.
- `translation` *(block)*: Global offset of the object `{x=..., y=..., z=...}`. *(Optional, default: `{x=0, y=0, z=0}`)*.
- `rotation` *(block)*: Euler rotation in degrees `{x=..., y=..., z=...}`. *(Optional, default: `{x=0, y=0, z=0}`)*.
- `material` *(string)*: Name of the material to apply to the object. *(Optional, default: BLACK)*.

> **Note:** Materials must be declared in a `materials = { ... };` block at the root of the configuration before being referenced by their name in the `material` parameter of a primitive.

---

## 3. Primitives

Primitives must be declared inside the main `primitives = { ... };` block. Each primitive type is a list bearing the plural name of the plugin (e.g., `spheres`, `planes`).

### 3.1. Sphere (`spheres`)

Represents a 3D sphere.

**Additional parameters:**

- `r` *(float)*: Sphere radius. **(Required)**

**Example:**

```cfg
spheres = (
    {
        position = { x = 0.0; y = 0.0; z = -10.0; };
        r = 2.0;
        translation = { x = 1.0; y = 0.0; z = 0.0; }; # Optional
        rotation = { x = 0.0; y = 45.0; z = 0.0; }; # Optional
        material = "my_red_material"; # Optional
    }
);
```

### 3.2. Plane (`planes`)

Represents an infinite plane. The plane is oriented upwards by default (Y axis: `0, 1, 0`). Use `rotation` to tilt it.

**Example:**

```cfg
planes = (
    {
        position = { x = 0.0; y = -2.0; z = 0.0; };
        rotation = { x = 90.0; y = 0.0; z = 0.0; }; # Optional
        translation = { x = 0.0; y = 0.0; z = 0.0; }; # Optional
        material = "floor_material"; # Optional
    }
);
```

### 3.3. Cylinder (`cylinders`)

Represents a cylinder (infinite or limited). By default, the cylinder axis points upwards (Y axis: `0, 1, 0`). Use `rotation` to tilt it.

**Additional parameters:**

- `r` *(float)*: Cylinder radius. Must be positive. **(Required)**
- `h` *(float, optional)*: Cylinder height. If absent, the cylinder will be infinite.

**Example:**

```cfg
cylinders = (
    {
        position = { x = 0.0; y = -2.0; z = -5.0; };
        r = 1.5;
        h = 5.0; # Remove for infinite
        rotation = { x = 0.0; y = 0.0; z = 45.0; }; # Optional
        translation = { x = 0.0; y = 0.0; z = 0.0; }; # Optional
        material = "column_material"; # Optional
    }
);
```

### 3.4. Triangle (`triangles`)

Represents a triangle defined by 3 vertices. The `position` and `rotation` apply to the vertices.

**Additional parameters:**

- `v0`, `v1`, `v2` *(blocks)*: The three base vertices of the triangle. Each must contain `{x, y, z}`. **(Required)**

**Example:**

```cfg
triangles = (
    {
        v0 = { x = -1.0; y = -1.0; z = -5.0; };
        v1 = { x =  1.0; y = -1.0; z = -5.0; };
        v2 = { x =  0.0; y =  1.0; z = -5.0; };
        translation = { x = 2.0; y = 0.0; z = 0.0; }; # Optional
        rotation = { x = 0.0; y = 0.0; z = 0.0; }; # Optional
        material = "blue_glass"; # Optional
    }
);
```

### 3.5. Obj (`objs`)

Loads a 3D model from an `.obj` file.

**Additional parameters:**

- `file` *(string)*: File path to the `.obj` file. **(Required)**
- `scale` *(float, optional)*: Scale factor to resize the model. Default: 1.0.
- `position` is defined in the `.obj` file.

**Example:**

```cfg
objs = (
    {
        file = "models/cube.obj";
        scale = 2.0;
        translation = { x = 0.0; y = 0.0; z = -5.0; }; # Optional
        rotation = { x = 45.0; y = 45.0; z = 0.0; }; # Optional
        material = "gold_metal"; # Optional
    }
);
```

### 3.6. Box (`boxes`)

Represents a 3D box (rectangular cuboid), defined by a `position`, a `rotation` and it's size along the three axes.

**Additional parameters:**

- `dimension` *(blocks)*: Size of the box along each axis `{x, y, z}`. **(Required)**
  - `x`: width
  - `y`: height
  - `z`: depth
  - All values must be **strictly positive**

**Example:**

```cfg
boxes = (
    {
        position = { x = -1.0; y = 0.0; z = 2.0; };
        dimension = { x =  1.5; y = 1.0; z = 1.0; };
        rotation = { x =  2.0; y =  0.0; z = 0.0; }; # Optional
        translation = { x = 0.0; y = 0.0; z = 0.0; }; # Optional
        material = "red"; # Optional
    }
);
```

### 3.7. Cone (`cones`)

Represents a cone (infinite or limited). By default, the cone axis points upwards (Y axis: `0, 1, 0`). Use `rotation` to tilt it.

**Additional parameters:**

- `r` *(float)*: Cone radius. Must be positive. **(Required)**
- `h` *(float, optional)*: Cone height *(for a limited cone)*.
- `d` *(float, optional)*: Distance along the cone axis from the apex, at which the cone reaches the specified radius `r` *(for an infinite cone)*.
- You must call either `h` or `d`. **(Required)**

**Example:**

Infinite:

```cfg
cones = (
    {
        position = { x = 0.0; y = -2.0; z = -5.0; };
        r = 1.0;
        d = 5.0; # Replace by `h` for limited
        rotation = { x = 0.0; y = 0.0; z = 45.0; }; # Optional
        translation = { x = 0.0; y = 0.0; z = 0.0; }; # Optional
        material = "column_material"; # Optional
    }
);
```

Limited:

```cfg
torus = (
    {
        position = { x = 0.0; y = -2.0; z = -5.0; };
        r = 1.0;
        h = 3.0; # Replace by `d` for infinite
        rotation = { x = 0.0; y = 0.0; z = 45.0; }; # Optional
        translation = { x = 0.0; y = 0.0; z = 0.0; }; # Optional
        material = "column_material"; # Optional
    }
);
```

### 3.8. Torus (`torus`)

Represents a torus in 3D space.

**Additional parameters:**

- `outer_radius` *(float)*: Torus outer radius. Must be positive. **(Required)**
- `inner_radius` *(float)*: Torus inner radius. Must be positive. **(Required)**

**Example:**

Infinite:

```cfg
cones = (
    {
        position = { x = 0.0; y = -2.0; z = -5.0; };
        outer_radius = 1.4;
        inner_radius = 0.8;
        rotation = { x = 0.0; y = 0.0; z = 45.0; }; # Optional
        translation = { x = 0.0; y = 0.0; z = 0.0; }; # Optional
        material = "column_material"; # Optional
    }
);
```

---

## 4. Materials

Materials define the appearance and light reaction of primitives. They must be declared in a `materials = { ... };` block at the root of the configuration file, before the primitives.

Each material must have a unique name (`name = "..."`) which will then be used by primitives via the `material` property.

### 4.1. Lambertian (`lambertian`)

Represents a classic matte (diffuse) material. It scatters light equally in all directions.

**Parameters:**

- `name` *(string)*: The material's unique identifier. **(Required)**
- `color` *(block, optional)*: The object's color `{r, g, b}`. *(Default: white)*

**Example:**

```cfg
materials = {
    lambertians = (
        { name = "my_red_material"; color = { r = 255.0; g = 0.0; b = 0.0; }; },
        { name = "floor_material";  color = { r = 100.0; g = 100.0; b = 100.0; }; }
    );
};
```

### 4.2. Texture (`texture`)

Represents an image-based material mapped onto a primitive using UV coordinates.

**Parameters:**

- `name` *(string)*: The material's unique identifier. **(Required)**
- `filepath` *(string)*: Path to the texture image file. **(Required)**

**Example:**

```cfg
materials = {
    textures = (
        {
            name = "MyTextureName";
            filepath = "texture/MyTexture.jpg";
        }
    );
};
```

### 4.3. Refractive (`refractive`)

Represents a refractive material that allows light to pass through, simulating glass or water.

**Parameters:**

- `name` *(string)*: The material's unique identifier. **(Required)**
- `color` *(block, optional)*: The base color of the material `{r, g, b}`. *(Default: white)*
- `transparency` *(float)*: The material's transparency level (0.0 to 1.0). **(Required)**
- `refractiveIndex` *(float)*: The material's refractive index. **(Required)**

**Example:**

```cfg
materials = {
    refractives = (
        {
            name = "MyRefractiveMaterial";
            color = { r = 255.0; g = 255.0; b = 255.0; }; # Optional
            transparency = 0.5;
            refractiveIndex = 1.5;
        }
    );
};
```

### 4.4. Reflective (`reflective`)

Represents a reflective/metallic material that mirrors its surroundings.

**Parameters:**

- `name` *(string)*: The material's unique identifier. **(Required)**
- `color` *(block, optional)*: The material's color tint `{r, g, b}`. *(Default: white)*
- `reflectiveIndex` *(float)*: Controls the surface smoothness/reflectivity. **(Required)**
  - Higher values: Smoother, more mirror-like reflections
  - Lower values: Rougher reflections with more diffusion
  - Can be any positive value (not limited to 0-1 range)

**Example:**

```cfg
materials = {
    reflectives = (
        {
            name = "polished_gold";
            color = { r = 255.0; g = 200.0; b = 0.0; };
            reflectiveIndex = 0.9;
        },
        {
            name = "brushed_steel";
            color = { r = 200.0; g = 200.0; b = 200.0; };
            reflectiveIndex = 0.6;
        }
    );
};
```

---

## 5. Lights

*Note: Unlike primitives which now use materials, lights continue to use the `color` parameter directly.*

### 5.1. AmbientLight

Global ambient light that uniformly illuminates all objects.

**Parameters:**

- `ambient` *(float, optional)*: Intensity of the ambient light (0.0 to 1.0). Default: 0.
- `color` *(block, optional)*: Tint `{r, g, b}`. Default: white.

**Example:**

```cfg
lights = {
    ambient = 0.2;
    color = { r = 255.0; g = 255.0; b = 255.0; }; # Optional
};
```

### 5.2. DirectionalLight (`directional`)

Directional light.

**Parameters:**

- `intensity` *(float)*: Light intensity. **(Required)**
- `direction` *(block)*: Direction vector `{x, y, z}`. Will be normalized. **(Required)**
- `color` *(block, optional)*: Light color. Default: white.

**Example:**

```cfg
lights = {
    directionals = (
        {
            intensity = 0.8;
            direction = { x = -1.0; y = -1.0; z = -1.0; };
            color = { r = 255.0; g = 255.0; b = 255.0; }; # Optional
        }
    );
};
```
