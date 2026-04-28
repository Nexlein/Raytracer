/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Plane
*/

/// @file Plane.cpp
/// @brief Implementation of the Plane class.

#include "Plane.hpp"

#include <cmath>
#include <memory>

#include "ConfigUtils.hpp"
#include "RayTracerException.hpp"

RayTracer::Plane::Plane(std::string axis, double position) : _position(position)
{
    if (axis != "X" && axis != "Y" && axis != "Z")
        throw RayTracer::RayTracerException("Plane: Axis must be 'X', 'Y', or 'Z'.");

    if (axis == "X")
        _normal = Vector3D(1, 0, 0);
    else if (axis == "Y")
        _normal = Vector3D(0, 1, 0);
    else
        _normal = Vector3D(0, 0, 1);
}

bool RayTracer::Plane::hits(const Ray& ray, HitRecord& rec) const
{
    double denom = ray._direction.dot(_normal);

    if (std::abs(denom) < 1e-6) return false;

    double t = (_position - ray._origin.dot(_normal)) / denom;

    if (t <= 0.001) return false;

    rec.distance = t;
    rec.p = ray._origin + (ray._direction * t);
    rec.normal = _normal;

    return true;
}

void RayTracer::Plane::init(const libconfig::Setting& setting)
{
    if (setting.exists("axis")) {
        std::string axis = setting["axis"];
        if (axis == "X")
            _normal = Vector3D(1, 0, 0);
        else if (axis == "Y")
            _normal = Vector3D(0, 1, 0);
        else
            _normal = Vector3D(0, 0, 1);
    }

    ConfigUtils::getAsDouble(setting, "position", _position);

    if (setting.exists("color")) {
        const libconfig::Setting& c = setting["color"];
        double r = 255.0;
        double g = 255.0;
        double b = 255.0;
        ConfigUtils::getAsDouble(c, "r", r);
        ConfigUtils::getAsDouble(c, "g", g);
        ConfigUtils::getAsDouble(c, "b", b);
        color._x = static_cast<int>(r);
        color._y = static_cast<int>(g);
        color._z = static_cast<int>(b);
    }
}

extern "C" {
RayTracer::IPrimitive* entryPoint()
{
    return new RayTracer::Plane("Z", 0.0);
}
}
