/*
** EPITECH PROJECT, 2026
** G-OOP-400-MPL-4-1-bsraytracer-11
** File description:
** Sphere
*/

#pragma once

#include "IPrimitive.hpp"
#include "Point3D.hpp"

namespace RayTracer {
    using Point3D = Math::Point3D<double>;
    using Vector3D = Math::Vector3D<double>;

    class Sphere : public IPrimitive {
        public:
        Sphere(const Point3D& center, double radius);

        Point3D _center;
        double _radius;

        [[nodiscard]] bool hits(const Ray& ray) const override;
    };
}  // namespace RayTracer
