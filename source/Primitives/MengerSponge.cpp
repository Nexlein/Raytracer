/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Manger Sponge
*/

#include "MengerSponge.hpp"

#include <algorithm>

#include "ConfigUtils.hpp"

void RayTracer::MengerSponge::init(const libconfig::Setting& setting)
{
    ConfigUtils::parsePoint3D(setting, "position", _position, true);

    ConfigUtils::parsePoint3D(setting, "rotation", _rotation, false);

    if (!ConfigUtils::getAsDouble(setting, "scale", _scale)) _scale = 1.0;

    if (!ConfigUtils::getAsDouble(setting, "iterations", _iterations))
        throw RayTracerException("Fractal: Invalid or missing required parameter 'iterations'");

    if (setting.exists("material")) {
        std::string name = setting["material"];
        _materialName = name;
    }
}

double RayTracer::MengerSponge::boxDE(const Math::Vector3D<double>& p, double size) const
{
    Math::Vector3D<double> q(std::abs(p._x) - size, std::abs(p._y) - size, std::abs(p._z) - size);
    return Math::Vector3D<double>(std::max(q._x, 0.0), std::max(q._y, 0.0), std::max(q._z, 0.0))
               .length() +
           std::min(std::max({q._x, q._y, q._z}), 0.0);
}

double RayTracer::MengerSponge::crossDE(const Math::Vector3D<double>& p) const
{
    double a = std::abs(p._x) - 1.0 / 3.0;
    double b = std::abs(p._y) - 1.0 / 3.0;
    double c = std::abs(p._z) - 1.0 / 3.0;
    // croix infinie sur les 3 axes
    double dxy = std::max(a, b);
    double dyz = std::max(b, c);
    double dxz = std::max(a, c);
    return std::min({dxy, dyz, dxz});
}

double RayTracer::MengerSponge::distanceEstimate(const Math::Vector3D<double>& pos) const
{
    Math::Vector3D<double> p = pos / _scale;
    double d = boxDE(p, 1.0);
    double s = 1.0;

    for (int i = 0; i < _iterations; ++i) {
        Math::Vector3D<double> a(std::fmod(p._x * s, 2.0) - 1.0, std::fmod(p._y * s, 2.0) - 1.0,
                                 std::fmod(p._z * s, 2.0) - 1.0);
        s *= 3.0;
        Math::Vector3D<double> r =
            Math::Vector3D<double>(std::abs(a._x), std::abs(a._y), std::abs(a._z)) * (1.0 / s);

        double c = crossDE(r);
        d = std::max(d, c);
    }
    return d * _scale;
}

extern "C" {
RayTracer::IPrimitive* entryPoint() { return new RayTracer::MengerSponge(); }
}
