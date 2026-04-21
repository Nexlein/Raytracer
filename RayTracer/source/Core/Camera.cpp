/*
** EPITECH PROJECT, 2026
** G-OOP-400-MPL-4-1-bsraytracer-11
** File description:
** Camera
*/

#include "Camera.hpp"

#include <cmath>

RayTracer::Camera::Camera(const Math::Point3D<double>& position,
                          const Math::Vector3D<double>& rotation, int width, int height, double fov)
    : _position(position), _rotation(rotation), _width(width), _height(height), _fieldOfView(fov)
{
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
