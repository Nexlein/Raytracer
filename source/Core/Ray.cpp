/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Ray
*/

/// @file Ray.cpp
/// @brief Implementation of the Ray class.

#include "Ray.hpp"

RayTracer::Ray::Ray(const Point3D& origin, const Vector3D& direction)
    : _origin(origin), _direction(direction)
{
}
