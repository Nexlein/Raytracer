/*
** EPITECH PROJECT, 2026
** G-OOP-400-MPL-4-1-bsraytracer-11
** File description:
** Sphere
*/

#include "Sphere.hpp"

#include "RayTracerException.hpp"

RayTracer::Sphere::Sphere(const Point3D& center, double radius) : _center(center), _radius(radius)
{
    if (radius < 0) throw RayTracer::RayTracerException("Sphere: Radius cannot be negative.");
}

bool RayTracer::Sphere::hits(const Ray& ray) const
{
    Vector3D originToCenter = ray._origin - _center;

    double a = ray._direction.dot(ray._direction);
    double b = 2.0 * ray._direction.dot(originToCenter);
    double c = originToCenter.dot(originToCenter) - (_radius * _radius);

    double discriminant = b * b - 4.0 * a * c;

    return discriminant >= 0.0;
}
