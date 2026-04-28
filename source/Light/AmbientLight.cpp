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
    _intensity = 0.0;
    ConfigUtils::getAsDouble(setting, "ambient", _intensity);

    _color = Math::Vector3D<double>(255.0, 255.0, 255.0);
    if (setting.exists("color")) {
        const libconfig::Setting& colorSetting = setting["color"];
        double r = 255.0, g = 255.0, b = 255.0;
        ConfigUtils::getAsDouble(colorSetting, "r", r);
        ConfigUtils::getAsDouble(colorSetting, "g", g);
        ConfigUtils::getAsDouble(colorSetting, "b", b);
        _color = Math::Vector3D<double>(r, g, b);
    }
}

extern "C" {
RayTracer::ILight* entryPoint() { return new RayTracer::AmbientLight(); }
}
