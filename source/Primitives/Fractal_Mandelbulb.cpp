/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Fractal_Mandelbulb
*/

#include "Fractal_Mandelbulb.hpp"
#include "ConfigUtils.hpp"

void RayTracer::Mandelbulb::init(const libconfig::Setting& setting)
{
    if (!ConfigUtils::getAsDouble(setting, "power", _power))
        throw RayTracerException("Mandelbulb: Missing required parameter 'power'");
}

double RayTracer::Mandelbulb::distanceEstimate(const Math::Vector3D<double>& pos) const
{
    Math::Vector3D<double> z = pos;
    double dr = 1.0;
    double r  = 0.0;

    for (int i = 0; i < _iterations; ++i) {
        r = z.length();
        if (r > _bailout) break;

        // coordonnées sphériques
        double theta = std::acos(z._z / r);
        double phi   = std::atan2(z._y, z._x);
        dr = std::pow(r, _power - 1.0) * _power * dr + 1.0;

        // z = z^power + pos
        double zr = std::pow(r, _power);
        theta *= _power;
        phi   *= _power;
        z = Math::Vector3D<double>(
            zr * std::sin(theta) * std::cos(phi),
            zr * std::sin(theta) * std::sin(phi),
            zr * std::cos(theta)
        ) + pos;
    }
    return 0.5 * std::log(r) * r / dr;  // DE de Hart et al.
}

extern "C" {
RayTracer::IPrimitive* entryPoint() { return new RayTracer::Mandelbulb(); }
}
