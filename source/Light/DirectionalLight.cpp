#include "DirectionalLight.hpp"

#include <algorithm>
#include <memory>

#include "ConfigUtils.hpp"

RayTracer::DirectionalLight::DirectionalLight(const Vector3D& direction, double intensity,
                                              Math::Vector3D<double> color)
    : _direction(direction.normalized())
{
    _intensity = intensity;
    _color = color;
}

Math::Vector3D<double> RayTracer::DirectionalLight::computeLight(const HitRecord& hit) const
{
    double dot = hit.normal.dot(_direction);
    double intensity = _intensity * std::max(0.0, dot);
    return (_color / 255.0) * intensity;
}

Math::Vector3D<double> RayTracer::DirectionalLight::getDirection() const { return _direction; }

void RayTracer::DirectionalLight::init(const libconfig::Setting& setting)
{
    _intensity = 0.0;
    if (!ConfigUtils::getAsDouble(setting, "diffuse", _intensity)) {
        try {
            const libconfig::Setting& parent = setting.getParent().getParent();
            ConfigUtils::getAsDouble(parent, "diffuse", _intensity);
        } catch (...) {
            // Ignore error : intensity = 0.0
        }
    }

    _color = Math::Vector3D<double>(255.0, 255.0, 255.0);
    if (setting.exists("color")) {
        const libconfig::Setting& colorSetting = setting["color"];
        double r = 255.0, g = 255.0, b = 255.0;
        ConfigUtils::getAsDouble(colorSetting, "r", r);
        ConfigUtils::getAsDouble(colorSetting, "g", g);
        ConfigUtils::getAsDouble(colorSetting, "b", b);
        _color = Math::Vector3D<double>(r, g, b);
    }

    double x = 0.0, y = 0.0, z = 0.0;
    if (setting.exists("direction")) {
        const libconfig::Setting& directionSetting = setting["direction"];
        ConfigUtils::getAsDouble(directionSetting, "x", x);
        ConfigUtils::getAsDouble(directionSetting, "y", y);
        ConfigUtils::getAsDouble(directionSetting, "z", z);
    }
    _direction = Math::Vector3D<double>(x, y, z).normalized();
}

extern "C" {
RayTracer::ILight* entryPoint() { return new RayTracer::DirectionalLight(); }
}
