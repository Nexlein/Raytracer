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

    rec.material = _material.get();
    if (std::abs(denom) < 1e-6) return false;

    Math::Vector3D<double> originToPlane = _position - ray._origin;
    double t = originToPlane.dot(_normal) / denom;

    if (t <= 0.001) return false;

    rec.distance = t;
    rec.p = ray._origin + (ray._direction * t);
    rec.normal = _normal;
    rec.material = _material.get();

    return true;
}

void RayTracer::Plane::init(const libconfig::Setting& setting)
{
    ConfigUtils::parsePoint3D(setting, "position", _position, true);

    Math::Vector3D<double> translation;
    ConfigUtils::parseVector3D(setting, "translation", translation, false);
    _position = _position + translation;

    Math::Vector3D<double> rotation;
    ConfigUtils::parseVector3D(setting, "rotation", rotation, false);

    if (setting.exists("material")) {
        std::string name = setting["material"];
        _materialName = name;
    }
    // Default normal is pointing up (Y axis)
    _normal = Vector3D(0.0, 1.0, 0.0);
    _normal.rotateX(rotation._x);
    _normal.rotateY(rotation._y);
    _normal.rotateZ(rotation._z);
    _normal = _normal.normalized();
}

extern "C" {
RayTracer::IPrimitive* entryPoint() { return new RayTracer::Plane(); }
}
