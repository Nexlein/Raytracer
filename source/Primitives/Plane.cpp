/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Plane
*/

/// @file Plane.cpp
/// @brief Implementation of the Plane class.

#include "Plane.hpp"

#include <cmath>

#include "RayTracerException.hpp"

RayTracer::Plane::Plane(std::string axis, int position) : _position(position)
{
    if (axis != "X" && axis != "Y" && axis != "Z")
        throw RayTracer::RayTracerException("Plane: Axis must be 'X', 'Y', or 'Z'.");

    if (axis == "X")
        _normal = Vector3D(1, 0, 0);
    else if (axis == "Y")
        _normal = Vector3D(0, 1, 0);
    else
        _normal = Vector3D(0, 0, 1);
}

bool RayTracer::Plane::hits(const Ray& ray, HitRecord& rec) const
{
    double denom = ray._direction.dot(_normal);

    if (std::abs(denom) < 1e-6) return false;

    double t = (_position - ray._origin.dot(_normal)) / denom;

    if (t <= 0.001) return false;

    rec.distance = t;
    rec.p = ray._origin + (ray._direction * t);
    rec.normal = _normal;

    return true;
}
