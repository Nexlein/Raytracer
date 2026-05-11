/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Lambertian
*/

#include "Lambertian.hpp"

#include "ConfigUtils.hpp"
#include "IPrimitive.hpp"
#include "MaterialUtils.hpp"
#include "RayTracerException.hpp"

void RayTracer::Lambertian::init(const libconfig::Setting& setting)
{
    if (!setting.lookupValue("name", _name))
        throw RayTracerException("Lambertian material must have a name");
    ConfigUtils::parseColor(setting, "color", _color);

    if (!ConfigUtils::getAsDouble(setting, "shininess", _shininess)) _shininess = 32;

    if (!ConfigUtils::getAsDouble(setting, "specularStrength", _specularStrength))
        _specularStrength = 0.5;
}

bool RayTracer::Lambertian::scatter(const Ray& /*rayIn*/, HitRecord& rec,
                                    Math::Vector3D<double>& attenuation, Ray& scattered) const
{
    Math::Vector3D<double> scatterDir = rec.normal + MaterialUtils::randomUnitVector();

    if (scatterDir.dot(scatterDir) < 1e-8) scatterDir = rec.normal;

    scattered = Ray(rec.p, scatterDir);
    attenuation = _color / 255.0;
    return true;
}

bool RayTracer::Lambertian::hasSpecular() const { return true; }

double RayTracer::Lambertian::getShininess() const { return _shininess; }

double RayTracer::Lambertian::getSpecularStrength() const { return _specularStrength; }

extern "C" {
RayTracer::IMaterial* entryPoint() { return new RayTracer::Lambertian(); }
}