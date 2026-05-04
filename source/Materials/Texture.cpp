/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Texture
*/

#include "Texture.hpp"

#include <cmath>
#include <iostream>

#include "IPrimitive.hpp"
#include "MaterialUtils.hpp"
#include "RayTracerException.hpp"

void RayTracer::Texture::init(const libconfig::Setting& setting)
{
    if (setting.exists("name"))
        _name = static_cast<const char*>(setting["name"]);
    else
        throw RayTracerException("Texture material must have a name");

    if (!setting.lookupValue("filepath", _filepath))
        throw RayTracerException("Texture: Missing 'filepath' parameter.");

    // Load the image using SFML
    if (!_image.loadFromFile(_filepath))
        throw RayTracerException("Texture: Failed to load image " + _filepath);
    _width = _image.getSize().x;
    _height = _image.getSize().y;
}

bool RayTracer::Texture::scatter(const Ray& /*rayIn*/, const HitRecord& rec,
                                 Math::Vector3D<double>& attenuation, Ray& scattered) const
{
    Math::Vector3D<double> scatterDir = rec.normal + MaterialUtils::randomUnitVector();

    if (scatterDir.dot(scatterDir) < 1e-8) scatterDir = rec.normal;

    scattered = Ray(rec.p, scatterDir);

    if (_width > 0 && _height > 0) {
        // Apply UV mapping
        double u = std::fmod(rec.u, 1.0);
        double v = std::fmod(rec.v, 1.0);
        if (u < 0) u += 1.0;
        if (v < 0) v += 1.0;

        unsigned int i = static_cast<unsigned int>(u * _width);
        unsigned int j = static_cast<unsigned int>((1.0 - v) * _height - 0.001);

        if (i >= static_cast<unsigned int>(_width)) i = _width - 1;
        if (j >= static_cast<unsigned int>(_height)) j = _height - 1;

        sf::Color pixel = _image.getPixel(i, j);
        double r = pixel.r / 255.0;
        double g = pixel.g / 255.0;
        double b = pixel.b / 255.0;

        attenuation = Math::Vector3D<double>(r, g, b);
    } else
        attenuation = Math::Vector3D<double>(1, 0, 1);

    return true;
}

extern "C" {
RayTracer::IMaterial* entryPoint() { return new RayTracer::Texture(); }
}
