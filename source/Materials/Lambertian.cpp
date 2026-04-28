/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Lambertian
*/

#include "Lambertian.hpp"
#include "RayTracerException.hpp"
#include "ConfigUtils.hpp"

RayTracer::Lambertian::Lambertian(std::string name,
                                  const Math::Vector3D<double>& color)
: _color(color) { _name = name; }

void RayTracer::Lambertian::init(const libconfig::Setting& setting)
{
    // init le name et color / changer comment les primitives gere leurs couleurs / puis tester
    if (!setting.lookupValue("name", _name))
        throw RayTracerException("Lambertian material must have a name");
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
RayTracer::IMaterial* entryPoint() { return new RayTracer::Lambertian(); }
}