/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Rectangle3D
*/

/// @file Rectangle3D.hpp
/// @brief Rectangle3D class definition

#pragma once

#include "Point3D.hpp"
#include "Vector3D.hpp"

/// @brief Namespace for the RayTracer project
namespace RayTracer {
    using Point3D = Math::Point3D<double>;
    using Vector3D = Math::Vector3D<double>;

    /// @brief Represents a rectangle in 3D space
    class Rectangle3D {
        public:
        /// @brief Constructs a Rectangle3D object
        /// @param origin The origin point of the rectangle in 3D space
        /// @param bottomSide The vector representing the bottom side of the rectangle
        /// @param leftSide The vector representing the left side of the rectangle
        Rectangle3D(const Point3D& origin, const Vector3D& bottomSide, const Vector3D& leftSide);

        /// @brief Origin point of the rectangle
        Point3D _origin;
        /// @brief Vector representing the bottom side of the rectangle
        Vector3D _bottomSide;
        /// @brief Vector representing the left side of the rectangle
        Vector3D _leftSide;

        /// @brief Computes the point on the rectangle corresponding to the given coordinates
        /// @param u The horizontal coordinate on the rectangle (0 to 1)
        /// @param v The vertical coordinate on the rectangle (0 to 1)
        /// @return A Point3D object representing the point on the rectangle corresponding to the
        /// specified coordinates
        [[nodiscard]] Point3D pointAt(double u, double v) const;
    };
}  // namespace RayTracer
