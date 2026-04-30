/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Renderer
*/

/// @file Renderer.cpp
/// @brief Implementation of the Renderer class.

#include "Renderer.hpp"

#include <fstream>

#include "ConfigUtils.hpp"
#include "RayTracerException.hpp"

void RayTracer::Renderer::init(const libconfig::Setting& setting)
{
    if (!setting.exists("resolution")) throw RayTracerException("Renderer: Missing resolution.");
    const libconfig::Setting& res = setting["resolution"];
    if (!res.lookupValue("width", _width) || !res.lookupValue("height", _height))
        throw RayTracerException("Renderer: Invalid or missing resolution width/height.");

    if (setting.exists("background")) {
        std::string bgName = setting["background"];
        _backgroundMaterialName = bgName;
    } else
        _backgroundMaterialName = "";
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
            Math::Vector3D<double> pixelColor = computeRayColor(r, 10, primitives, lights);
            writeColor(outFile, pixelColor);
        }
    }

    outFile.close();
}
