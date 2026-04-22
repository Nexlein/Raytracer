/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** PrimitiveFactory
*/

/// @file PrimitiveFactory.hpp
/// @brief Factory for creating primitives

#pragma once

#include <libconfig.h++>
#include <memory>
#include <string>

#include "IPrimitive.hpp"

/// @brief Namespace for the Ray Tracer project
namespace RayTracer {
    /// @brief Factory class for creating primitives from configuration settings
    class PrimitiveFactory {
        public:
        /// @brief Creates a sphere primitive from the given configuration setting
        /// @param setting The configuration setting containing the parameters for the sphere
        /// @return A unique pointer to the created sphere primitive
        [[nodiscard]] std::unique_ptr<IPrimitive> createSphere(const libconfig::Setting& setting);

        /// @brief Creates a plane primitive from the given configuration setting
        /// @param setting The configuration setting containing the parameters for the plane
        /// @return A unique pointer to the created plane primitive
        [[nodiscard]] std::unique_ptr<IPrimitive> createPlane(const libconfig::Setting& setting);
    };
}  // namespace RayTracer
