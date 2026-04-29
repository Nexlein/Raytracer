#include "AmbientLight.hpp"

#include <memory>

#include "ConfigUtils.hpp"

RayTracer::AmbientLight::AmbientLight(double intensity, Math::Vector3D<double> color)
{
    _intensity = intensity;
    _color = color;
}

Math::Vector3D<double> RayTracer::AmbientLight::computeLight(
    [[maybe_unused]] const HitRecord& hit) const
{
    return (_color / 255.0) * _intensity;
}

bool RayTracer::AmbientLight::castsShadow() const { return false; }

void RayTracer::AmbientLight::init(const libconfig::Setting& setting)
{
    if (!ConfigUtils::getAsDouble(setting, "ambient", _intensity))
        throw RayTracerException("AmbientLight: Missing required parameter 'ambient'.");

    ConfigUtils::parseColor(setting, "color", _color);
}

extern "C" {
RayTracer::ILight* entryPoint() { return new RayTracer::AmbientLight(); }
}
