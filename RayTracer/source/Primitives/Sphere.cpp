/*
** EPITECH PROJECT, 2026
** G-OOP-400-MPL-4-1-bsraytracer-11
** File description:
** Sphere
*/

#include "Sphere.hpp"

#include <cmath>

#include "RayTracerException.hpp"

RayTracer::Sphere::Sphere(const Point3D& center, double radius) : _center(center), _radius(radius)
{
    if (radius < 0) throw RayTracer::RayTracerException("Sphere: Radius cannot be negative.");
}

bool RayTracer::Sphere::hits(const Ray& ray, HitRecord& rec) const
{
    Vector3D originToCenter = ray._origin - _center;

    double a = ray._direction.dot(ray._direction);
    double b = 2.0 * ray._direction.dot(originToCenter);
    double c = originToCenter.dot(originToCenter) - (_radius * _radius);

    double discriminant = b * b - 4.0 * a * c;

    if (discriminant < 0) return false;

    double sqrtd = std::sqrt(discriminant);
    double root = (-b - sqrtd) / (2.0 * a);
    if (root <= 0.001) {
        root = (-b + sqrtd) / (2.0 * a);
        if (root <= 0.001) return false;
    }

    rec.distance = root;
    rec.p = ray._origin + (ray._direction * rec.distance);
    rec.normal = (rec.p - _center) / _radius;

    return true;
}
