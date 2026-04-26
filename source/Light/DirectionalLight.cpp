#include "DirectionalLight.hpp"

RayTracer::DirectionalLight::DirectionalLight(const Vector3D& direction, double intensity)
: _direction(direction.normalized()), _intensity(intensity) {}

double RayTracer::DirectionalLight::computeDiffuse(const HitRecord& hit) const
{
    double dot = hit.normal.dot(_direction);
    return _intensity * std::max(0.0, dot);
}
