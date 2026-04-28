/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Lambertian
*/

#pragma once

#include "IMaterial.hpp"
#include "Vector3D.hpp"

namespace RayTracer {
    class Lambertian : public IMaterial {
        public:
        Lambertian() = default;

        /// @brief Create a lambertian material
        /// @param name Name of the material
        /// @param color Color of the material
        Lambertian(std::string name, const Math::Vector3D<double>& color);

        /// @brief Initializes the material with settings from a configuration file
        /// @param setting The configuration settings for the material
        void init(const libconfig::Setting& setting) override;

        private:
        /// @brief Color of the lambertian material
        Math::Vector3D<double> _color;
    };
}
