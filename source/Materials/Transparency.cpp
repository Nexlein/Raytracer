/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Transparency
*/

#include "Transparency.hpp"

#include "IPrimitive.hpp"
#include "ConfigUtils.hpp"
#include "MaterialUtils.hpp"
#include "RayTracerException.hpp"

RayTracer::Transparency::Transparency(std::string name, Math::Vector3D<double> color,
                                      double transparency, double refractiveIndex)
    : _transparency(transparency), _refractiveIndex(refractiveIndex)
{
    _name = name;
    _color = color;
}

void RayTracer::Transparency::init(const libconfig::Setting& setting)
{
    if (!setting.lookupValue("name", _name))
        throw RayTracerException("Lambertian material must have a name");

    ConfigUtils::parseColor(setting, "color", _color);

    if (!ConfigUtils::getAsDouble(setting, "transparency", _transparency))
        throw RayTracerException("Transparent material must have a transparency parameter");

    if (!ConfigUtils::getAsDouble(setting, "refractiveIndex", _refractiveIndex))
        throw RayTracerException("Transparent material must have a refraction parameter");
}

bool RayTracer::Transparency::scatter(const Ray& rayIn, const HitRecord& rec,
                                      Math::Vector3D<double>& attenuation, Ray& scattered) const
{
    // Si transparency = 0 -> comportement opaque, on ne scatter pas
    if (_transparency <= 0.0)
        return false;

    attenuation = Math::Vector3D<double>(1.0, 1.0, 1.0);

    bool frontFace = rayIn._direction.dot(rec.normal) < 0;
    Math::Vector3D<double> normal = frontFace ? rec.normal : -rec.normal;
    double ratio = frontFace ? (1.0 / _refractiveIndex) : _refractiveIndex;

    Math::Vector3D<double> unitDir = rayIn._direction.normalized();
    double cosTheta = std::min<double>((-unitDir).dot(normal), 1.0);
    double sinTheta = std::sqrt(1.0 - cosTheta * cosTheta);

    bool mustReflect = ratio * sinTheta > 1.0;
    bool fresnelReflect = MaterialUtils::schlick(cosTheta, ratio) > MaterialUtils::randomDouble();

    Math::Vector3D<double> _direction;
    if (mustReflect || fresnelReflect)
        _direction = MaterialUtils::reflect(unitDir, normal);
    else
        _direction = MaterialUtils::refract(unitDir, normal, ratio);

    attenuation = _color / 255.0; // dans scatter()
    scattered = Ray(rec.p + _direction * 0.01, _direction);
    return true;
}

extern "C" {
RayTracer::IMaterial* entryPoint() { return new RayTracer::Transparency(); }
}