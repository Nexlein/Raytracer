/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Renderer
*/

/// @file Renderer.hpp
/// @brief Renderer class for ray tracing rendering

#pragma once

#include <algorithm>
#include <iostream>
#include <libconfig.h++>
#include <limits>
#include <memory>
#include <string>
#include <vector>

#include "Camera.hpp"
#include "ILight.hpp"
#include "IPrimitive.hpp"
#include "Vector3D.hpp"

/// @brief Namespace for the Ray Tracer project
namespace RayTracer {
    /// @brief Renderer class responsible for rendering the scene
    class Renderer {
        public:
        /// @brief Default constructor
        Renderer() = default;

        /// @brief Initializes the renderer with settings from a configuration file
        /// @param setting The configuration settings for the renderer
        void init(const libconfig::Setting& setting);

        /// @brief Renders the scene to an image file
        /// @param camera The camera to use for rendering
        /// @param primitives The list of primitives in the scene
        /// @param lights The list of lights in the scene
        /// @param filename The name of the output image file
        void render(const Camera& camera,
                    const std::vector<std::unique_ptr<IPrimitive>>& primitives,
                    const std::vector<std::unique_ptr<ILight>>& lights,
                    const std::string& filename) const;

        private:
        /// @brief Width of the output image
        int _width;
        /// @brief Height of the output image
        int _height;
        /// @brief Background color of the scene
        Math::Vector3D<double> _backgroundColor;

        /// @brief Checks if a point is in shadow
        /// @param hit The hit record
        /// @param lightDir The direction to the light
        /// @param primitives The list of primitives in the scene
        /// @return True if the point is in shadow, false otherwise
        [[nodiscard]] inline bool isInShadow(
            const HitRecord& hit, const Math::Vector3D<double>& lightDir,
            const std::vector<std::unique_ptr<IPrimitive>>& primitives) const
        {
            Ray shadowRay(hit.p + hit.normal * 0.001, lightDir);
            HitRecord tempRec;
            for (const auto& primitive : primitives) {
                if (primitive->hits(shadowRay, tempRec) && tempRec.distance > 0.001) return true;
            }
            return false;
        }

        /// @brief Computes the color for a given ray based on the scene's primitives
        /// @param ray The ray to trace
        /// @param primitives The list of primitives in the scene
        /// @param lights The list of lights in the scene
        /// @return The computed color for the ray
        [[nodiscard]] inline Math::Vector3D<double> computeRayColor(
            const Ray& ray, const std::vector<std::unique_ptr<IPrimitive>>& primitives,
            const std::vector<std::unique_ptr<ILight>>& lights) const
        {
            bool hitAnything = false;
            HitRecord tempRec;
            HitRecord closestRec;
            double closest = std::numeric_limits<double>::infinity();
            const IPrimitive* hitPrimitive = nullptr;

            for (const auto& primitive : primitives) {
                if (primitive->hits(ray, tempRec)) {
                    if (tempRec.distance < closest && tempRec.distance > 0.001) {
                        closest = tempRec.distance;
                        closestRec = tempRec;
                        hitPrimitive = primitive.get();
                        hitAnything = true;
                    }
                }
            }

            if (hitAnything) {
                Math::Vector3D<double> totalLight(0.0, 0.0, 0.0);
                for (const auto& light : lights) {
                    if (!light->castsShadow() ||
                        !isInShadow(closestRec, light->getDirection(), primitives))
                        totalLight += light->computeLight(closestRec);
                }

                // clamp 0-1
                totalLight._x = std::clamp(totalLight._x, 0.0, 1.0);
                totalLight._y = std::clamp(totalLight._y, 0.0, 1.0);
                totalLight._z = std::clamp(totalLight._z, 0.0, 1.0);

                // primitive.color en 0-255, totalLight en 0-1 → résultat en 0-255
                return (hitPrimitive->color / 255.0) * totalLight * 255.0;
            }

            return _backgroundColor;
        }

        /// @brief Writes the color of a pixel to the output stream
        /// @param out The output stream to write the color to
        /// @param color The color to write
        inline void writeColor(std::ostream& out, const Math::Vector3D<double>& color) const
        {
            out << static_cast<int>(color._x) << ' ' << static_cast<int>(color._y) << ' '
                << static_cast<int>(color._z) << '\n';
        }
    };
}  // namespace RayTracer
