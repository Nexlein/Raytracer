/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** DirectionalLight
*/

#include "ILight.hpp"
#include "math.h"

#pragma once

namespace RayTracer {
    class DirectionalLight : public ILight {
    public:
        /// @brief Constructor for DirectionalLight
        /// @param direction direction of the light
        /// @param intensity intensity of the light
        DirectionalLight(const Vector3D& direction, double intensity);

        /// @brief Computes the diffuse lighting for a given hit record
        /// @param hit The hit record for which to compute diffuse lighting
        /// @return The computed diffuse lighting value
        [[nodiscard]] double computeDiffuse(const HitRecord& hit) const override;

    private:
        // Direction of the light, used for rendering
        Vector3D _direction;

        // Intensity of the light, used for rendering
        double _intensity;
    };
}