/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Camera
*/

/// @file Camera.cpp
/// @brief Implementation of the Camera class.

#include "Camera.hpp"

RayTracer::Camera::Camera(const Point3D& origin, const Rectangle3D& screen)
    : _origin(origin), _screen(screen)
{
}

RayTracer::Ray RayTracer::Camera::ray(double u, double v) const
{
    return Ray(_origin, _screen.pointAt(u, v) - _origin);
}
