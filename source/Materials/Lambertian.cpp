/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Lambertian
*/

#include "Lambertian.hpp"

#include "ConfigUtils.hpp"
#include "MaterialUtils.hpp"
#include "RayTracerException.hpp"

RayTracer::Lambertian::Lambertian(std::string name, const Math::Vector3D<double>& color)
{
    _name = name;
    _color = color;
}

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

bool RayTracer::Lambertian::scatter(const Ray& /*rayIn*/, const HitRecord& rec,
                                    Math::Vector3D<double>& attenuation, Ray& scattered) const
{
    Math::Vector3D<double> scatterDir = rec.normal + MaterialUtils::randomUnitVector();

    if (scatterDir.dot(scatterDir) < 1e-8) scatterDir = rec.normal;

    scattered = Ray(rec.p, scatterDir);
    attenuation = _color / 255.0;
    return true;
}

extern "C" {
RayTracer::IMaterial* entryPoint() { return new RayTracer::Lambertian(); }
}