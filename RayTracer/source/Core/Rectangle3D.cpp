/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Rectangle3D
*/

/// @file Rectangle3D.cpp
/// @brief Implementation of the Rectangle3D class.
#include "Rectangle3D.hpp"

#include "RayTracerException.hpp"

RayTracer::Rectangle3D::Rectangle3D(const Point3D& origin, const Vector3D& bottomSide,
                                    const Vector3D& leftSide)
    : _origin(origin), _bottomSide(bottomSide), _leftSide(leftSide)
{
    if (bottomSide.length() == 0 || leftSide.length() == 0)
        throw RayTracer::RayTracerException("Rectangle3D: Side length cannot be zero.");
}

Math::Point3D<double> RayTracer::Rectangle3D::pointAt(double u, double v) const
{
    return _origin + (_bottomSide * u) + (_leftSide * v);
}
