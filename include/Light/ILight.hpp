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
        /// @return Retourne l'intensité diffuse [0.0, 1.0] pour un point donné
        [[nodiscard]] virtual double computeDiffuse(const HitRecord& hit) const = 0;
    };
}
