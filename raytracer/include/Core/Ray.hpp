/*
** EPITECH PROJECT, 2026
** G-OOP-400-MPL-4-1-bsraytracer-11
** File description:
** Ray
*/

#pragma once

#include "Point3D.hpp"
#include "Vector3D.hpp"

namespace RayTracer {
    using Point3D = Math::Point3D<double>;
    using Vector3D = Math::Vector3D<double>;

    class Ray {
        public:
        Ray(const Point3D& origin, const Vector3D& direction);

        Point3D _origin;
        Vector3D _direction;
    };
}  // namespace RayTracer
