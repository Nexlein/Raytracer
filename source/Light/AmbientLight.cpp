#include "AmbientLight.hpp"

RayTracer::AmbientLight::AmbientLight(double intensity,  Math::Vector3D<double> color)
{
    _intensity = intensity;
    _color = color;
}

Math::Vector3D<double> RayTracer::AmbientLight::computeDiffuse(
    [[maybe_unused]] const HitRecord& hit) const
{
    return (_color / 255.0) * _intensity;
}

bool RayTracer::AmbientLight::castsShadow() const { return false; }
