/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Plane
*/

/// @file Plane.hpp
/// @brief Plane class definition

#pragma once

#include "IPrimitive.hpp"
#include "Point3D.hpp"
#include <string>

/// @brief Namespace for the RayTracer project
namespace RayTracer {
    using Point3D = Math::Point3D<double>;
    using Vector3D = Math::Vector3D<double>;

    /// @brief Represents a plane in 3D space
    class Plane : public IPrimitive {
        public:
        /// @brief Constructs a plane object
        /// @param axis The axis along which the plane is oriented (X, Y, or Z)
        /// @param position The position of the plane along the specified axis
        Plane(std::string axis, int position);

        /// @brief Normal vector of the plane
        Vector3D _normal;

        /// @brief Position of the plane in 3D space
        int _position;

        /// @brief Determines if a ray intersects the plane and fills the hit record with intersection details
        /// @param ray The ray to test for intersection with the plane
        /// @param hitRecord The hit record to be filled with intersection details if the ray hits the plane
        /// @return True if the ray intersects the plane, false otherwise
        [[nodiscard]] bool hits(const Ray& ray, HitRecord& hitRecord) const override;
    };
}