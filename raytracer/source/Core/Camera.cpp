/*
** EPITECH PROJECT, 2026
** G-OOP-400-MPL-4-1-bsraytracer-11
** File description:
** Camera
*/

#include "Camera.hpp"

RayTracer::Camera::Camera(const Point3D& origin, const Rectangle3D& screen)
    : _origin(origin), _screen(screen)
{
}

RayTracer::Ray RayTracer::Camera::ray(double u, double v) const
{
    return Ray(_origin, _screen.pointAt(u, v) - _origin);
}
