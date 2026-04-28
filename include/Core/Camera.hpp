/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Camera
*/

/// @file Camera.hpp
/// @brief Camera class definition

#pragma once

#include <libconfig.h++>

#include "Point3D.hpp"
#include "Ray.hpp"
#include "Vector3D.hpp"

/// @brief Namespace for the RayTracer project
namespace RayTracer {
    /// @brief Represents a camera in 3D space for ray tracing
    class Camera {
        public:
        /// @brief Default constructor
        Camera() = default;

        /// @brief Construct a Camera object
        /// @param position Position of the camera in 3D space
        /// @param rotation Rotation of the camera in degrees
        /// @param width Width of the camera's viewport in pixels
        /// @param height Height of the camera's viewport in pixels
        /// @param fieldOfView Field of view of the camera in degrees
        Camera(const Math::Point3D<double>& position, const Math::Vector3D<double>& rotation,
               int width, int height, double fieldOfView);

        /// @brief Generates a ray from the camera through a point on the screen
        /// @param u The horizontal coordinate on the screen (0 to 1)
        /// @param v The vertical coordinate on the screen (0 to 1)
        /// @return A Ray object representing the ray from the camera through the specified point on
        /// the screen
        [[nodiscard]] Ray ray(double u, double v) const;

        /// @brief Initializes the camera with settings from a configuration file
        /// @param setting The configuration settings for the camera
        void init(const libconfig::Setting& setting);

        /// @brief Gets the background color of the scene
        /// @return The background color
        [[nodiscard]] Math::Vector3D<double> getBackgroundColor() const;

        /// @brief Sets the background color of the scene
        /// @param color The new background color
        void setBackgroundColor(const Math::Vector3D<double>& color);

        private:
        /// @brief Background color of the scene
        Math::Vector3D<double> _backgroundColor;

        /// @brief Position of the camera in 3D space
        Math::Point3D<double> _position;
        /// @brief Rotation of the camera in degrees
        Math::Vector3D<double> _rotation;
        /// @brief Width of the camera's viewport in pixels
        int _width;
        /// @brief Height of the camera's viewport in pixels
        int _height;
        /// @brief Field of view of the camera in degrees
        double _fieldOfView;
    };
}  // namespace RayTracer
