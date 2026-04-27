/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Renderer
*/

/// @file Renderer.hpp
/// @brief Renderer class for ray tracing rendering

#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Camera.hpp"
#include "IPrimitive.hpp"
#include "ILight.hpp"
#include "Vector3D.hpp"

/// @brief Namespace for the Ray Tracer project
namespace RayTracer {
    /// @brief Renderer class responsible for rendering the scene
    class Renderer {
        public:
        /// @brief Renders the scene to an image file
        /// @param camera The camera to use for rendering
        /// @param primitives The list of primitives in the scene
        /// @param lights The list of lights in the scene
        /// @param width The width of the output image
        /// @param height The height of the output image
        /// @param filename The name of the output image file
        void render(const Camera& camera,
                    const std::vector<std::unique_ptr<IPrimitive>>& primitives,
                    const std::vector<std::unique_ptr<ILight>>& lights, int width,
                    int height, const std::string& filename) const;

        private:
        /// @brief Computes the color for a given ray based on the scene's primitives
        /// @param ray The ray to trace
        /// @param primitives The list of primitives in the scene
        /// @param lights The list of lights in the scene
        /// @return The computed color for the ray
        [[nodiscard]] Math::Vector3D<double> computeRayColor(
            const Ray& ray, const std::vector<std::unique_ptr<IPrimitive>>& primitives,
            const std::vector<std::unique_ptr<ILight>>& lights) const;

        /// @brief Writes the color of a pixel to the output stream
        /// @param out The output stream to write the color to
        /// @param color The color to write
        void writeColor(std::ostream& out, const Math::Vector3D<double>& color) const;
    };
}  // namespace RayTracer
