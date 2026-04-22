/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** IPrimitive
*/

/// @file IPrimitive.hpp
/// @brief IPrimitive interface definition

#pragma once

#include "Ray.hpp"

/// @brief Namespace for the RayTracer project
namespace RayTracer {
    /// @brief Interface for geometric primitives that can be intersected by rays
    class IPrimitive {
        public:
        virtual ~IPrimitive() = default;

        /// @brief Determines if a ray hits the primitive
        /// @param ray The ray to test for intersection with the primitive
        /// @return True if the ray intersects with the primitive, false otherwise
        [[nodiscard]] virtual bool hits(const Ray& ray) const = 0;
    };
}  // namespace RayTracer
