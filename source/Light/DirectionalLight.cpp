#include "DirectionalLight.hpp"

RayTracer::DirectionalLight::DirectionalLight(const Vector3D& direction, double intensity, Math::Vector3D<double> color)
: _direction(direction.normalized())
{
    _intensity = intensity;
    _color = color;
}

Math::Vector3D<double> RayTracer::DirectionalLight::computeDiffuse(const HitRecord& hit) const
{
    double dot = hit.normal.dot(_direction);
    double intensity = _intensity * std::max(0.0, dot);
    return (_color / 255.0) * intensity;
}
