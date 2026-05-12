/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** PointLight - Light source emitting from a specific position (implementation)
*/

#include "PointLight.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <memory>

#include "ConfigUtils.hpp"

void RayTracer::PointLight::init(const libconfig::Setting& setting)
{
    // Parse required intensity parameter
    if (!ConfigUtils::getAsDouble(setting, "intensity", _intensity))
        throw RayTracerException("PointLight: Missing required parameter 'intensity'.");

    // Parse required position parameter
    ConfigUtils::parsePoint3D(setting, "position", _position, true);

    // Parse optional translation and apply it to position
    Vector3D translation;
    ConfigUtils::parseVector3D(setting, "translation", translation, false);
    _position = _position + translation;

    // Parse optional rotation
    ConfigUtils::parseVector3D(setting, "rotation", _rotation, false);
}

extern "C" {
RayTracer::ILight* entryPoint() { return new RayTracer::PointLight(); }
}
