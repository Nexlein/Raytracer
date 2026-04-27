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
        /// @param color color of the light
        DirectionalLight(const Vector3D& direction, double intensity, Math::Vector3D<double> color);

        [[nodiscard]] Math::Vector3D<double> computeDiffuse([[maybe_unused]] const HitRecord& hit) const override;

    private:
        // Direction of the light, used for rendering
        Vector3D _direction;
    };
}