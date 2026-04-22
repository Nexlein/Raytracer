/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** PrimitiveFactory
*/

/// @file PrimitiveFactory.hpp
/// @brief Factory for creating primitives

#pragma once

#include <memory>
#include <string>

#include "IPrimitive.hpp"
#include "SceneParser.hpp"

/// @brief Namespace for the Ray Tracer project
namespace RayTracer {
    /// @brief Factory class for creating primitives from configuration settings
    class PrimitiveFactory {
        public:
        /// @brief Creates a sphere primitive from the given parsed data
        /// @param sphere The parsed sphere data
        /// @return A unique pointer to the created sphere primitive
        [[nodiscard]] std::unique_ptr<IPrimitive> createSphere(const SphereData& sphere);

        /// @brief Creates a plane primitive from the given configuration setting
        /// @param plane The parsed plane data
        /// @return A unique pointer to the created plane primitive
        [[nodiscard]] std::unique_ptr<IPrimitive> createPlane(const PlaneData& plane);
    };
}  // namespace RayTracer
