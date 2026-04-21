/*
** EPITECH PROJECT, 2026
** G-OOP-400-MPL-4-1-bsraytracer-11
** File description:
** Ray
*/

#include "Ray.hpp"

RayTracer::Ray::Ray(const Point3D& origin, const Vector3D& direction)
    : _origin(origin), _direction(direction)
{
}
