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
    _position = applyRotation(_position);

    parseCommonProperties(setting);

    ConfigUtils::getAsDouble(setting, "constant_attenuation", _constantAttenuation);
    ConfigUtils::getAsDouble(setting, "linear_attenuation", _linearAttenuation);
    ConfigUtils::getAsDouble(setting, "quadratic_attenuation", _quadraticAttenuation);
}

Math::Vector3D<double> RayTracer::PointLight::computeLight(const HitRecord& hit) const
{
    Vector3D toLight = getDirection(hit);
    double distance = (_position - hit.p).length();
    double attenuation = calculateAttenuation(distance);
    double intensity = _intensity * std::max(0.0, hit.normal.dot(toLight)) * attenuation;

    return (_color / 255.0) * intensity;
}

RayTracer::Vector3D<double> RayTracer::PointLight::getDirection(const HitRecord& hit) const
{
    return (_position - hit.p).normalized();
}

RayTracer::Vector3D<double> RayTracer::PointLight::applyRotation(Vector3D vec) const
{
    if (_rotation.length() == 0.0)
        return vec;

    const double rx = _rotation._x * M_PI / 180.0;
    const double ry = _rotation._y * M_PI / 180.0;
    const double rz = _rotation._z * M_PI / 180.0;

    const double y1 = vec._y * std::cos(rx) - vec._z * std::sin(rx);
    const double z1 = vec._y * std::sin(rx) + vec._z * std::cos(rx);
    vec._y = y1;
    vec._z = z1;

    const double x2 = vec._x * std::cos(ry) + vec._z * std::sin(ry);
    const double z2 = -vec._x * std::sin(ry) + vec._z * std::cos(ry);
    vec._x = x2;
    vec._z = z2;

    const double x3 = vec._x * std::cos(rz) - vec._y * std::sin(rz);
    const double y3 = vec._x * std::sin(rz) + vec._y * std::cos(rz);
    vec._x = x3;
    vec._y = y3;

    return vec;
}

double RayTracer::PointLight::calculateAttenuation(double distance) const
{
    if (distance < 0.001)
        distance = 0.001;

    const double denominator = _constantAttenuation
        + _linearAttenuation * distance
        + _quadraticAttenuation * distance * distance;

    return std::max(0.0, 1.0 / denominator);
}

extern "C" RayTracer::ILight* entryPoint()
{
    return new RayTracer::PointLight();
}
