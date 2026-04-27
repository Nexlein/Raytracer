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
        /// @param direction direction of the light
        /// @param intensity intensity of the light
        AmbientLight(double intensity);

        /// @brief Computes the diffuse lighting for a given hit record
        /// @param hit The hit record for which to compute diffuse lighting
        /// @return The computed diffuse lighting value
        [[nodiscard]] double computeDiffuse([[maybe_unused]] const HitRecord& hit) const override;

    private:
        // Intensity of the light, used for rendering
        double _intensity;
    };
}