/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Triangle
*/

/// @file Triangle.hpp
/// @brief Triangle class definition

#pragma once

#include "IPrimitive.hpp"
#include "Point3D.hpp"

/// @brief Namespace for the RayTracer project
namespace RayTrace {
    using Point3D = Math::Point3D<double>;
    using Vector3D = Math::Vector3D<double>;

    /// @brief Represents a triangle in 3D space
    class Triangle : public IPrimitive {
        public:
        Triangle() = default;
        /// @brief Constructs a Triangle object
        /// @param v0 The first vertex of the triangle
        /// @param v1 The second vertex of the triangle
        /// @param v2 The third vertex of the triangle
        Triangle(const Point3D& v0, const Point3D& v1, const Point3D& v2);
        
    };
} // namespace RayTracer
