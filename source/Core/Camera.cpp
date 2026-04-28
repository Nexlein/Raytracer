/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Camera
*/

/// @file Camera.cpp
/// @brief Implementation of the Camera class.

#include "Camera.hpp"

#include <cmath>

#include "ConfigUtils.hpp"
#include "RayTracerException.hpp"

RayTracer::Camera::Camera(const Math::Point3D<double>& position,
                          const Math::Vector3D<double>& rotation, int width, int height, double fov)
    : _backgroundColor(0, 0, 255),
      _position(position),
      _rotation(rotation),
      _width(width),
      _height(height),
      _fieldOfView(fov)
{
}

void RayTracer::Camera::init(const libconfig::Setting& setting)
{
    if (!setting.exists("resolution")) throw RayTracerException("Camera: Missing resolution.");
    const libconfig::Setting& res = setting["resolution"];
    if (!res.lookupValue("width", _width) || !res.lookupValue("height", _height))
        throw RayTracerException("Camera: Invalid or missing resolution width/height.");

    double px = 0, py = 0, pz = 0;
    if (setting.exists("position")) {
        const libconfig::Setting& pos = setting["position"];
        ConfigUtils::getAsDouble(pos, "x", px);
        ConfigUtils::getAsDouble(pos, "y", py);
        ConfigUtils::getAsDouble(pos, "z", pz);
    }
    _position = Math::Point3D<double>(px, py, pz);

    double rx = 0, ry = 0, rz = 0;
    if (setting.exists("rotation")) {
        const libconfig::Setting& rot = setting["rotation"];
        ConfigUtils::getAsDouble(rot, "x", rx);
        ConfigUtils::getAsDouble(rot, "y", ry);
        ConfigUtils::getAsDouble(rot, "z", rz);
    }
    _rotation = Math::Vector3D<double>(rx, ry, rz);

    _fieldOfView = 90.0;
    ConfigUtils::getAsDouble(setting, "fieldOfView", _fieldOfView);

    _backgroundColor = Math::Vector3D<double>(0, 0, 255);
    if (setting.exists("backgroundColor")) {
        const libconfig::Setting& colorSetting = setting["backgroundColor"];
        double r = 0, g = 0, b = 255;
        ConfigUtils::getAsDouble(colorSetting, "r", r);
        ConfigUtils::getAsDouble(colorSetting, "g", g);
        ConfigUtils::getAsDouble(colorSetting, "b", b);
        _backgroundColor = Math::Vector3D<double>(r, g, b);
    }
}

RayTracer::Ray RayTracer::Camera::ray(double u, double v) const
{
    double ratio = static_cast<double>(_width) / _height;

    double scale = std::tan(_fieldOfView * 0.5 * M_PI / 180.0);

    double px = (2.0 * u - 1.0) * ratio * scale;
    double py = (2.0 * v - 1.0) * scale;

    Math::Vector3D<double> direction(px, py, 1.0);

    direction.rotateX(_rotation._x);
    direction.rotateY(_rotation._y);
    direction.rotateZ(_rotation._z);

    return Ray(_position, direction);
}

Math::Vector3D<double> RayTracer::Camera::getBackgroundColor() const
{
    return _backgroundColor;
}

void RayTracer::Camera::setBackgroundColor(const Math::Vector3D<double>& color)
{
    _backgroundColor = color;
}
