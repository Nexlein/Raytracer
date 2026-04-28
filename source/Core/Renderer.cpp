/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Renderer
*/

/// @file Renderer.cpp
/// @brief Implementation of the Renderer class.

#include "Renderer.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>

#include "RayTracerException.hpp"

void RayTracer::Renderer::writeColor(std::ostream& out, const Math::Vector3D<double>& color) const
{
    out << static_cast<int>(color._x) << ' ' << static_cast<int>(color._y) << ' '
        << static_cast<int>(color._z) << '\n';
}

void RayTracer::Renderer::render(const Camera& camera,
                                 const std::vector<std::unique_ptr<IPrimitive>>& primitives,
                                 const std::vector<std::unique_ptr<ILight>>& lights, int width,
                                 int height, const std::string& filename) const
{
    std::ofstream outFile(filename);
    if (!outFile.is_open())
        throw RayTracerException("Renderer: Cannot open output file " + filename);

    outFile << "P3\n" << width << ' ' << height << "\n255\n";

    for (int y = height; y >= 0; y--) {
        for (int x = 0; x < width; x++) {
            double u = static_cast<double>(x) / (width - 1);
            double v = static_cast<double>(y) / (height - 1);

            Ray r = camera.ray(u, v);
            Math::Vector3D<double> pixelColor = computeRayColor(r, camera, primitives, lights);
            writeColor(outFile, pixelColor);
        }
    }

    outFile.close();
}

bool RayTracer::Renderer::isInShadow(
    const HitRecord& hit, const Math::Vector3D<double>& lightDir,
    const std::vector<std::unique_ptr<IPrimitive>>& primitives) const
{
    // Ray depuis le hit point vers la lumière
    Ray shadowRay(hit.p + hit.normal * 0.001, lightDir);  // offset évite l'auto-intersection

    HitRecord tempRec;
    for (const auto& primitive : primitives) {
        if (primitive->hits(shadowRay, tempRec) && tempRec.distance > 0.001)
            return true;  // quelque chose bloque
    }
    return false;
}

Math::Vector3D<double> RayTracer::Renderer::computeRayColor(
    const Ray& ray, const Camera& camera,
    const std::vector<std::unique_ptr<IPrimitive>>& primitives,
    const std::vector<std::unique_ptr<ILight>>& lights) const
{
    bool hitAnything = false;
    HitRecord tempRec;
    HitRecord closestRec;
    double closest = std::numeric_limits<double>::infinity();
    const IPrimitive* hitPrimitive = nullptr;

    for (const auto& primitive : primitives) {
        if (primitive->hits(ray, tempRec)) {
            if (tempRec.distance < closest && tempRec.distance > 0.001) {
                closest = tempRec.distance;
                closestRec = tempRec;
                hitPrimitive = primitive.get();
                hitAnything = true;
            }
        }
    }

    if (hitAnything) {
        Math::Vector3D<double> totalLight(0.0, 0.0, 0.0);
        for (const auto& light : lights) {
            if (!light->castsShadow() || !isInShadow(closestRec, light->getDirection(), primitives))
                totalLight += light->computeLight(closestRec);
        }

        // clamp 0-1
        totalLight._x = std::clamp(totalLight._x, 0.0, 1.0);
        totalLight._y = std::clamp(totalLight._y, 0.0, 1.0);
        totalLight._z = std::clamp(totalLight._z, 0.0, 1.0);

        // primitive.color en 0-255, totalLight en 0-1 → résultat en 0-255
        return (hitPrimitive->color / 255.0) * totalLight * 255.0;
    }

    return camera.getBackgroundColor();
}
