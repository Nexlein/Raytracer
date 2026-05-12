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

    /// @brief Represents a point light source in 3D space
    /// @details A point light emits light in all directions from a specific position
    class PointLight : public ALight {
        public:
        /// @brief Default constructor for PointLight
        PointLight() = default;
    };
}  // namespace RayTracer
