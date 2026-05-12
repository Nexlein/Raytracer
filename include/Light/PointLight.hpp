/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** PointLight - Light source emitting from a specific position
*/

#pragma once

#include "ALight.hpp"
#include "Point3D.hpp"
#include "math.h"

namespace RayTracer {
    using Point3D = Math::Point3D<double>;
    using Vector3D = Math::Vector3D<double>;

    /// @brief Represents a point light source in 3D space
    /// @details A point light emits light in all directions from a specific position
    class PointLight : public ALight {
        public:
        /// @brief Default constructor for PointLight
        PointLight() = default;

        /// @brief Initializes the point light with settings from a configuration file
        /// @param setting The configuration settings for the light
        void init(const libconfig::Setting& setting) override;

        private:
        /// @brief Position of the point light in world space
        Point3D _position = {0, 0, 0};

        /// @brief Rotation of the light (for potential future use)
        Vector3D _rotation = {0.0, 0.0, 0.0};
    };
}  // namespace RayTracer
