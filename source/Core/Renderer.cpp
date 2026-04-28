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

#include "ConfigUtils.hpp"
#include "RayTracerException.hpp"

void RayTracer::Renderer::init(const libconfig::Setting& setting)
{
    if (!setting.exists("resolution")) throw RayTracerException("Renderer: Missing resolution.");
    const libconfig::Setting& res = setting["resolution"];
    if (!res.lookupValue("width", _width) || !res.lookupValue("height", _height))
        throw RayTracerException("Renderer: Invalid or missing resolution width/height.");

    _backgroundColor = Math::Vector3D<double>(0, 0, 255);
    if (setting.exists("backgroundColor")) {
        const libconfig::Setting& colorSetting = setting["backgroundColor"];
        double r = 0, g = 0, b = 255;
        ConfigUtils::getAsDouble(colorSetting, "r", r);
        ConfigUtils::getAsDouble(colorSetting, "g", g);
        ConfigUtils::getAsDouble(colorSetting, "b", b);
        _backgroundColor = Math::Vector3D<double>(r, g, b);
    }
}

void RayTracer::Renderer::writeColor(std::ostream& out, const Math::Vector3D<double>& color) const
{
    out << static_cast<int>(color._x) << ' ' << static_cast<int>(color._y) << ' '
        << static_cast<int>(color._z) << '\n';
}

void RayTracer::Renderer::render(const Camera& camera,
                                 const std::vector<std::unique_ptr<IPrimitive>>& primitives,
                                 const std::vector<std::unique_ptr<ILight>>& lights,
                                 const std::string& filename) const
{
    std::ofstream outFile(filename);
    if (!outFile.is_open())
        throw RayTracerException("Renderer: Cannot open output file " + filename);

    outFile << "P3\n" << _width << ' ' << _height << "\n255\n";

    double ratio = static_cast<double>(_width) / _height;

    for (int y = _height - 1; y >= 0; y--) {
        for (int x = 0; x < _width; x++) {
            double u = static_cast<double>(x) / (_width - 1);
            double v = static_cast<double>(y) / (_height - 1);

            Ray r = camera.ray(u, v, ratio);
            Math::Vector3D<double> pixelColor = computeRayColor(r, primitives, lights);
            writeColor(outFile, pixelColor);
        }
    }

    outFile.close();
}

bool RayTracer::Renderer::isInShadow(
    const HitRecord& hit, const Math::Vector3D<double>& lightDir,
    const std::vector<std::unique_ptr<IPrimitive>>& primitives) const
{
    Ray shadowRay(hit.p + hit.normal * 0.001, lightDir);

    HitRecord tempRec;
    for (const auto& primitive : primitives) {
        if (primitive->hits(shadowRay, tempRec) && tempRec.distance > 0.001) return true;
    }
    return false;
}

Math::Vector3D<double> RayTracer::Renderer::computeRayColor(
    const Ray& ray, const std::vector<std::unique_ptr<IPrimitive>>& primitives,
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

    return _backgroundColor;
}
