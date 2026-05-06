/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** AFractal
*/

#include "AFractal.hpp"
#include "ConfigUtils.hpp"
#include "RayTracerException.hpp"

void RayTracer::AFractal::init(const libconfig::Setting& setting)
{
    ConfigUtils::parsePoint3D(setting, "position", _position, true);

    if (!ConfigUtils::getAsDouble(setting, "scale", _scale))
        _scale = 1.0;

    if (!ConfigUtils::getAsDouble(setting, "iterations", _iterations))
        throw RayTracerException("Fractal: Invalid or missing required parameter 'iterations'");

    if (!ConfigUtils::getAsDouble(setting, "bailout", _bailout))
        throw RayTracerException("Fractal: Invalid or missing required parameter 'bailout'");

    if (setting.exists("material")) {
        std::string name = setting["material"];
        _materialName = name;
    }
}

bool RayTracer::AFractal::hits(const Ray& ray, HitRecord& hitRecord) const
{
    double t = 0.001;
    constexpr int MAX_STEPS = 300;
    constexpr double MAX_DIST = 100.0;
    constexpr double EPSILON  = 0.0001;

    for (int i = 0; i < MAX_STEPS; ++i) {
        Math::Point3D<double> p = ray._origin + ray._direction * t;
        double d = distanceEstimate(p - _position);

        if (d < EPSILON) {
            hitRecord.distance = t;
            hitRecord.p = p;
            hitRecord.normal = computeNormal(p - _position);
            hitRecord.material->setColor(_material->getColor());
            return true;
        }
        t += d;
        if (t > MAX_DIST) return false;
    }
    return false;
}

Math::Vector3D<double> RayTracer::AFractal::computeNormal(const Math::Vector3D<double>& p) const
{
    constexpr double H = 0.0001;
    double dx = distanceEstimate({p._x+H, p._y,   p._z  })
              - distanceEstimate({p._x-H, p._y,   p._z  });
    double dy = distanceEstimate({p._x,   p._y+H, p._z  })
              - distanceEstimate({p._x,   p._y-H, p._z  });
    double dz = distanceEstimate({p._x,   p._y,   p._z+H})
              - distanceEstimate({p._x,   p._y,   p._z-H});
    return Math::Vector3D<double>(dx, dy, dz).normalized();
}