# Raytracer Plugins Documentation

This document lists all the available parameters for each plugin (Primitives and Lights) of your Raytracer rendering engine, as well as the expected syntax in a `.cfg` configuration file.

---

## Common Parameters (Standardized)

To simplify scene creation, **all** primitives now use this unified parameter base:

- `position` *(block)*: Object coordinates `{x=..., y=..., z=...}`. **(Required for Sphere, Plane, Cylinder)**.
- `translation` *(block)*: Global offset of the object `{x=..., y=..., z=...}`. *(Optional, default: `{x=0, y=0, z=0}`)*.
- `rotation` *(block)*: Euler rotation in degrees `{x=..., y=..., z=...}`. *(Optional, default: `{x=0, y=0, z=0}`)*.
- `material` *(string)*: Name of the material to apply to the object. *(Optional, default: BLACK)*.

> **Note:** Materials must be declared in a `materials = { ... };` block at the root of the configuration before being referenced by their name in the `material` parameter of a primitive.

---

## 1. Primitives

Primitives must be declared inside the main `primitives = { ... };` block. Each primitive type is a list bearing the plural name of the plugin (e.g., `spheres`, `planes`).

### 1.1. Sphere (`spheres`)

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

### 1.2. Plane (`planes`)

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

### 1.3. Cylinder (`cylinders`)

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

### 1.4. Triangle (`triangles`)

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

### 1.5. Obj (`objs`)

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

---

## 2. Materials

Materials define the appearance and light reaction of primitives. They must be declared in a `materials = { ... };` block at the root of the configuration file, before the primitives.

Each material must have a unique name (`name = "..."`) which will then be used by primitives via the `material` property.

### 2.1. Lambertian (`lambertian`)

Represents a classic matte (diffuse) material. It scatters light equally in all directions.

**Parameters:**

- `name` *(string)*: The material's unique identifier. **(Required)**
- `color` *(block, optional)*: The object's color `{r, g, b}`. *(Default: white)*

**Example:**

```cfg
materials = {
    lambertian = (
        { name = "my_red_material"; color = { r = 255.0; g = 0.0; b = 0.0; }; },
        { name = "floor_material";  color = { r = 100.0; g = 100.0; b = 100.0; }; }
    );
};
```

---

## 3. Lights

*Note: Unlike primitives which now use materials, lights continue to use the `color` parameter directly.*

### 3.1. AmbientLight

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

### 3.2. DirectionalLight (`directional`)

Directional light.

**Parameters:**

- `intensity` *(float)*: Light intensity. **(Required)**
- `direction` *(block)*: Direction vector `{x, y, z}`. Will be normalized. **(Required)**
- `color` *(block, optional)*: Light color. Default: white.

**Example:**

```cfg
lights = {
    directional = (
        {
            intensity = 0.8;
            direction = { x = -1.0; y = -1.0; z = -1.0; };
            color = { r = 255.0; g = 255.0; b = 255.0; }; # Optional
        }
    );
};
```
