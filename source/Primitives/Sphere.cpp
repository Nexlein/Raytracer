/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Sphere
*/

/// @file Sphere.cpp
/// @brief Implementation of the Sphere class.

#include "Sphere.hpp"

#include <cmath>
#include <memory>

#include "ConfigUtils.hpp"
#include "RayTracerException.hpp"

bool RayTracer::Sphere::hits(const Ray& ray, HitRecord& rec) const
{
    Vector3D originToCenter = ray._origin - _center;

    double a = ray._direction.dot(ray._direction);
    double b = 2.0 * ray._direction.dot(originToCenter);
    double c = originToCenter.dot(originToCenter) - (_radius * _radius);

    double discriminant = b * b - 4.0 * a * c;

    if (discriminant < 0) return false;

    double sqrtd = std::sqrt(discriminant);
    double root = (-b - sqrtd) / (2.0 * a);
    if (root <= 0.001) {
        root = (-b + sqrtd) / (2.0 * a);
        if (root <= 0.001) return false;
    }

    rec.distance = root;
    rec.p = ray._origin + (ray._direction * rec.distance);
    rec.normal = (rec.p - _center) / _radius;
    rec.material = _material.get();
    return true;
}

void RayTracer::Sphere::init(const libconfig::Setting& setting)
{
    ConfigUtils::parsePoint3D(setting, "position", _center, true);

    Math::Vector3D<double> translation;
    ConfigUtils::parseVector3D(setting, "translation", translation, false);
    _center = _center + translation;

    if (!ConfigUtils::getAsDouble(setting, "r", _radius))
        throw RayTracer::RayTracerException("Sphere: Missing required parameter 'r'.");

    if (_radius < 0) throw RayTracer::RayTracerException("Sphere: Radius cannot be negative.");

    if (setting.exists("material")) {
        std::string name = setting["material"];
        _materialName = name;
    }
}

extern "C" {
RayTracer::IPrimitive* entryPoint() { return new RayTracer::Sphere(); }
}
