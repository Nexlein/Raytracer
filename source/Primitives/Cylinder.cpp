/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** Cylinder.cpp
*/

/// @file Cylinder.cpp
/// @brief Implementation of the Cylinder class.

#include "Cylinder.hpp"

#include <cmath>
#include <memory>

#include "ConfigUtils.hpp"
#include "RayTracerException.hpp"

/// @brief Namespace for the RayTracer project
namespace RayTracer {

    bool Cylinder::hits(const Ray& ray, HitRecord& rec) const
    {
        const double EPS = 1e-6;

        Vector3D originToBase = ray._origin - _base;
        Vector3D axis = _axis.normalized();

        Vector3D dD = ray._direction - axis * ray._direction.dot(axis);
        Vector3D dO = originToBase - axis * originToBase.dot(axis);

        double a = dD.dot(dD);
        double b = 2.0 * dD.dot(dO);
        double c = dO.dot(dO) - _radius * _radius;

        double closest = std::numeric_limits<double>::max();
        Vector3D normal;
        bool hit = false;

        double discriminant = b * b - 4.0 * a * c;
        if (discriminant >= 0 && std::abs(a) > EPS) {
            double sqrtd = std::sqrt(discriminant);
            double t1 = (-b - sqrtd) / (2 * a);
            double t2 = (-b + sqrtd) / (2 * a);

            for (double t : {t1, t2}) {
                if (t < EPS) continue;

                Point3D P = ray._origin + ray._direction * t;
                double h = (P - _base).dot(axis);

                bool inBounds = !_height.has_value() || (h >= 0 && h <= _height.value());
                if (inBounds && t < closest) {
                    closest = t;
                    hit = true;

                    Vector3D radial = (P - _base) - axis * h;
                    normal = radial.normalized();
                }
            }
        }

        if (_height.has_value()) {
            double denom = ray._direction.dot(axis);

            if (std::abs(denom) > EPS) {
                double t = (_base - ray._origin).dot(axis) / denom;
                if (t > EPS && t < closest) {
                    Point3D P = ray._origin + ray._direction * t;
                    Vector3D v = P - _base;

                    if (v.dot(v) <= _radius * _radius) {
                        closest = t;
                        hit = true;
                        normal = axis * -1.0;
                    }
                }

                Point3D top = _base + axis * _height.value();
                t = (top - ray._origin).dot(axis) / denom;

                if (t > EPS && t < closest) {
                    Point3D P = ray._origin + ray._direction * t;
                    Vector3D v = P - top;

                    if (v.dot(v) <= _radius * _radius) {
                        closest = t;
                        hit = true;
                        normal = axis;
                    }
                }
            }
        }

        if (!hit) return false;

        rec.distance = closest;
        rec.p = ray._origin + ray._direction * closest;
        rec.normal = normal;

        return true;
    }

    void Cylinder::init(const libconfig::Setting& setting)
    {
        double x = 0.0;
        double y = 0.0;
        double z = 0.0;

        ConfigUtils::getAsDouble(setting, "x", x);
        ConfigUtils::getAsDouble(setting, "y", y);
        ConfigUtils::getAsDouble(setting, "z", z);

        _base = Math::Point3D<double>(x, y, z);

        ConfigUtils::getAsDouble(setting, "ox", x);
        ConfigUtils::getAsDouble(setting, "oy", y);
        ConfigUtils::getAsDouble(setting, "oz", z);

        _axis = Math::Vector3D(x, y, z);

        _radius = 1.0;
        ConfigUtils::getAsDouble(setting, "r", _radius);

        if (_radius < 0) throw RayTracerException("Cylinder: Radius cannot be negative.");

        if (setting.exists("h")) {
            double h = 0.0;
            ConfigUtils::getAsDouble(setting, "h", h);
            _height = h;
        } else
            _height = std::nullopt;

        if (_height.has_value() && _height.value() < 0)
            throw RayTracerException("Cylinder: Height cannot be negative.");

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
    IPrimitive* entryPoint() { return new Cylinder(); }
    }
}  // namespace RayTracer
