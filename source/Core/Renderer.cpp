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
#include "MaterialUtils.hpp"

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
            Math::Vector3D<double> pixelColor(0.0, 0.0, 0.0);
            int samples = 50; // ajuste selon perf

            for (int s = 0; s < samples; s++) {
                double u = (x + MaterialUtils::randomDouble()) / (_width - 1);
                double v = (y + MaterialUtils::randomDouble()) / (_height - 1);
                Ray r = camera.ray(u, v, ratio);
                pixelColor += computeRayColor(r, 10, primitives, lights);
            }
            pixelColor = pixelColor / static_cast<double>(samples);
            writeColor(outFile, pixelColor);
        }
    }

    outFile.close();
}
