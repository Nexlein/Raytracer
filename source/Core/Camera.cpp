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
                          const Math::Vector3D<double>& rotation, double fov)
    : _position(position), _rotation(rotation), _fieldOfView(fov)
{
}

void RayTracer::Camera::init(const libconfig::Setting& setting)
{
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
}

RayTracer::Ray RayTracer::Camera::ray(double u, double v, double ratio) const
{
    double scale = std::tan(_fieldOfView * 0.5 * M_PI / 180.0);

    double px = (2.0 * u - 1.0) * ratio * scale;
    double py = (2.0 * v - 1.0) * scale;

    Math::Vector3D<double> direction(px, py, 1.0);

    direction.rotateX(_rotation._x);
    direction.rotateY(_rotation._y);
    direction.rotateZ(_rotation._z);

    return Ray(_position, direction);
}
