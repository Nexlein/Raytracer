/*
** EPITECH PROJECT, 2026
** G-OOP-400-MPL-4-1-bsraytracer-11
** File description:
** Camera
*/

#pragma once

#include "Point3D.hpp"
#include "Ray.hpp"
#include "Vector3D.hpp"

namespace RayTracer {
    class Camera {
        public:
        /// @brief Construct a Camera object
        /// @param position Position of the camera in 3D space
        /// @param rotation Rotation of the camera in degrees
        /// @param width Width of the camera's viewport in pixels
        /// @param height Height of the camera's viewport in pixels
        /// @param fieldOfView Field of view of the camera in degrees
        Camera(const Math::Point3D<double>& position, const Math::Vector3D<double>& rotation,
               int width, int height, double fieldOfView);

        [[nodiscard]] Ray ray(double u, double v) const;

        private:
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
