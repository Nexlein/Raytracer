/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** ILight
*/

#pragma once

#include "IPrimitive.hpp"

namespace RayTracer {
    class ILight {
        public:
        virtual ~ILight() = default;
        /// @brief Color of the light, used for rendering
        /// @param hit The hit record for which to compute the light
        /// @return Retourne la couleur de la lumière
        [[nodiscard]] virtual Math::Vector3D<double> computeDiffuse([[maybe_unused]] const HitRecord& hit) const = 0;

        protected:
        // Intensity of the light, used for rendering
        double _intensity;

        // Color of the light, used for rendering
        Math::Vector3D<double> _color;
    };
}
