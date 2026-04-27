/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** AmbientLight
*/

#include "ILight.hpp"
#include "math.h"

#pragma once

namespace RayTracer {
    class AmbientLight : public ILight {
    public:
        /// @brief Constructor for AmbientLight
        /// @param intensity intensity of the light
        /// @param color color of the light
        AmbientLight(double intensity, Math::Vector3D<double> color);

        [[nodiscard]] Math::Vector3D<double> computeDiffuse([[maybe_unused]] const HitRecord& hit) const override;
    };
}