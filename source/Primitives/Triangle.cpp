/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Triangle
*/

/// @file Triangle.cpp
/// @brief Implementation of the Triangle class.

#include "Triangle.hpp"

#include <cmath>
#include <memory>

#include "ConfigUtils.hpp"
#include "RayTracerException.hpp"

RayTracer::Triangle::Triangle(
    const Point3D& v0, const Point3D& v1, const Point3D& v2) :
    _v0(v0), _v1(v1), _v2(v2)
{
    if (v0._x == v1._x && v0._y == v1._y && v0._z == v1._z)
        throw RayTracer::RayTracerException("Triangle: Vertices cannot be the same point.");
    if (v0._x == v2._x && v0._y == v2._y && v0._z == v2._z)
        throw RayTracer::RayTracerException("Triangle: Vertices cannot be the same point.");
    if (v1._x == v2._x && v1._y == v2._y && v1._z == v2._z)
        throw RayTracer::RayTracerException("Triangle: Vertices cannot be the same point.");
    
    Vector3D edge1 = v1 - v0;
    Vector3D edge2 = v2 - v0;
    Vector3D normal(
        edge1._y * edge2._z - edge1._z * edge2._y,
        edge1._z * edge2._x - edge1._x * edge2._z,
        edge1._x * edge2._y - edge1._y * edge2._x);

    if (normal._x == 0.0 && normal._y == 0.0 && normal._z == 0.0)
        throw RayTracer::RayTracerException("Triangle: Vertices cannot be collinear.");
}

bool RayTracer::Triangle::hits(const Ray& ray, HitRecord& rec) const
{
}

extern "C" {
RayTracer::IPrimitive* entryPoint() { return new RayTracer::Triangle(); }
}
