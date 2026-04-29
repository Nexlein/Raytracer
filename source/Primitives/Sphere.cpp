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

    return true;
}

void RayTracer::Sphere::init(const libconfig::Setting& setting)
{
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;

    ConfigUtils::getAsDouble(setting, "x", x);
    ConfigUtils::getAsDouble(setting, "y", y);
    ConfigUtils::getAsDouble(setting, "z", z);

    _center = Math::Point3D<double>(x, y, z);

    _radius = 1.0;
    ConfigUtils::getAsDouble(setting, "r", _radius);

    if (_radius < 0) throw RayTracer::RayTracerException("Sphere: Radius cannot be negative.");

    if (setting.exists("color")) {
        const libconfig::Setting& c = setting["color"];
        double r = 255.0;
        double g = 255.0;
        double b = 255.0;
        ConfigUtils::getAsDouble(c, "r", r);
        ConfigUtils::getAsDouble(c, "g", g);
        ConfigUtils::getAsDouble(c, "b", b);
        _color._x = static_cast<int>(r);
        _color._y = static_cast<int>(g);
        _color._z = static_cast<int>(b);
    }
}

extern "C" {
RayTracer::IPrimitive* entryPoint() { return new RayTracer::Sphere(); }
}
