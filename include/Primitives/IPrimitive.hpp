/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** IPrimitive
*/

/// @file IPrimitive.hpp
/// @brief IPrimitive interface definition

#pragma once

#include <libconfig.h++>

#include "Ray.hpp"

/// @brief Namespace for the Ray Tracer project
namespace RayTracer {
    /// @brief Struct to hold hit record information when a ray intersects a primitive
    struct HitRecord {
        /// @brief Distance from the ray origin to the hit point
        double distance;
        /// @brief Point of intersection in 3D space
        Math::Point3D<double> p;
        /// @brief Normal vector at the point of intersection
        Math::Vector3D<double> normal;
    };

    /// @brief Interface for geometric primitives that can be intersected by rays
    class IPrimitive {
        public:
        virtual ~IPrimitive() = default;

        /// @brief Color of the primitive, used for rendering
        Math::Vector3D<double> color;

        /// @brief Initializes the primitive with settings from a configuration file
        /// @param setting The configuration settings for the primitive
        virtual void init(const libconfig::Setting& setting) = 0;

        /// @brief Determines if a ray intersects the primitive and fills the hit record with
        /// intersection details
        /// @param ray The ray to test for intersection with the primitive
        /// @param hitRecord The hit record to be filled with intersection details if the ray hits
        /// the primitive
        /// @return True if the ray intersects the primitive, false otherwise
        [[nodiscard]] virtual bool hits(const Ray& ray, HitRecord& hitRecord) const = 0;
    };
}  // namespace RayTracer
