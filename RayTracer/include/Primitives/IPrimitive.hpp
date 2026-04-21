/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** IPrimitive
*/

#pragma once

#include "Ray.hpp"

/// @brief Namespace for the Ray Tracer project
namespace RayTracer {
    /// @brief Struct to hold hit record information when a ray intersects a primitive
    struct HitRecord {
        double distance;
        Math::Point3D<double> p;
        Math::Vector3D<double> normal;
    };

    class IPrimitive {
        public:
        virtual ~IPrimitive() = default;

        /// @brief Color of the primitive, used for rendering
        Math::Vector3D<double> color;

        [[nodiscard]] virtual bool hits(const Ray& ray, HitRecord& rec) const = 0;
    };
}  // namespace RayTracer
