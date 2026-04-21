/*
** EPITECH PROJECT, 2026
** G-OOP-400-MPL-4-1-bsraytracer-11
** File description:
** Rectangle3D
*/

#pragma once

#include "Point3D.hpp"
#include "Vector3D.hpp"

namespace RayTracer {
    using Point3D = Math::Point3D<double>;
    using Vector3D = Math::Vector3D<double>;

    class Rectangle3D {
        public:
        Rectangle3D(const Point3D& origin, const Vector3D& bottomSide, const Vector3D& leftSide);

        Point3D _origin;
        Vector3D _bottomSide;
        Vector3D _leftSide;

        [[nodiscard]] Point3D pointAt(double u, double v) const;
    };
}  // namespace RayTracer
