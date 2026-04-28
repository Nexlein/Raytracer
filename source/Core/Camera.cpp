/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Camera
*/

/// @file Camera.cpp
/// @brief Implementation of the Camera class.

#include "Camera.hpp"

#include "ConfigUtils.hpp"

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
