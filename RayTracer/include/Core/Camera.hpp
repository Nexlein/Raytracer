/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Camera
*/

/// @file Camera.hpp
/// @brief Camera class definition

#pragma once

#include "Point3D.hpp"
#include "Ray.hpp"
#include "Rectangle3D.hpp"

/// @brief Namespace for the RayTracer project
namespace RayTracer {
    using Point3D = Math::Point3D<double>;

    /// @brief Represents a camera
    class Camera {
        public:
        /// @brief Constructs a Camera object
        /// @param origin The position of the camera in 3D space
        /// @param screen The rectangular screen representing the camera's view
        Camera(const Point3D& origin, const Rectangle3D& screen);

        /// @brief Origin point of the camera
        Point3D _origin;
        /// @brief Rectangular screen representing the camera's view
        Rectangle3D _screen;

        /// @brief Generates a ray from the camera through a point on the screen
        /// @param u The horizontal coordinate on the screen (0 to 1)
        /// @param v The vertical coordinate on the screen (0 to 1)
        /// @return A Ray object representing the ray from the camera through the specified point on
        /// the screen
        [[nodiscard]] Ray ray(double u, double v) const;
    };
}  // namespace RayTracer
