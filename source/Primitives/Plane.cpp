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
        else if (axis == "Z")
            _normal = Vector3D(0, 0, 1);
        else
            throw RayTracer::RayTracerException("Plane: Axis must be 'X', 'Y', or 'Z'.");
    }

    ConfigUtils::getAsDouble(setting, "position", _position);

    if (setting.exists("material")) {
        std::string name = setting["material"];
        materialName = name;
    }
}

extern "C" {
RayTracer::IPrimitive* entryPoint() { return new RayTracer::Plane(); }
}
