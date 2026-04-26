#include "AmbientLight.hpp"

RayTracer::AmbientLight::AmbientLight(double intensity) : _intensity(intensity) {}

double RayTracer::AmbientLight::computeDiffuse(
    [[maybe_unused]] const HitRecord& hit) const
{
    return _intensity;
}