/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Sphere
*/

/// @file Sphere.hpp
/// @brief Sphere class definition

#pragma once

#include "IPrimitive.hpp"
#include "Point3D.hpp"

/// @brief Namespace for the RayTracer project
namespace RayTracer {
    using Point3D = Math::Point3D<double>;
    using Vector3D = Math::Vector3D<double>;

    /// @brief Represents a sphere in 3D space
    class Sphere : public IPrimitive {
        public:
        /// @brief Constructs a Sphere object
        /// @param center The center point of the sphere in 3D space
        /// @param radius The radius of the sphere
        Sphere(const Point3D& center, double radius);

        /// @brief Center point of the sphere
        Point3D _center;
        /// @brief Radius of the sphere
        double _radius;

        /// @brief Determines if a ray hits the sphere
        /// @param ray The ray to test for intersection with the sphere
        /// @return True if the ray intersects with the sphere, false otherwise
        [[nodiscard]] bool hits(const Ray& ray) const override;
    };
}  // namespace RayTracer
