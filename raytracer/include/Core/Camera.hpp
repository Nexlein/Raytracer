/*
** EPITECH PROJECT, 2026
** G-OOP-400-MPL-4-1-bsraytracer-11
** File description:
** Camera
*/

#pragma once

#include "Point3D.hpp"
#include "Ray.hpp"
#include "Rectangle3D.hpp"

namespace RayTracer {
    using Point3D = Math::Point3D<double>;

    class Camera {
        public:
        Camera(const Point3D& origin, const Rectangle3D& screen);

        Point3D _origin;
        Rectangle3D _screen;

        [[nodiscard]] Ray ray(double u, double v) const;
    };
}  // namespace RayTracer
