/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Transparency
*/

#pragma once

#include "AMaterial.hpp"
#include "Vector3D.hpp"

namespace RayTracer {
    class Transparency : public AMaterial {
        public:
        Transparency() = default;

        /// @brief Create a transparent material
        /// @param name Name of the material
        /// @param transparency Transparency index of the material
        /// @param refractiveIndex refrative index of the material
        Transparency(std::string name, Math::Vector3D<double> color, double transparency,
                     double refractiveIndex);

        /// @brief Initializes the material with settings from a configuration file
        /// @param setting The configuration settings for the material
        void init(const libconfig::Setting& setting) override;

        bool scatter(const Ray& rayIn, const HitRecord& rec, Math::Vector3D<double>& attenuation,
                     Ray& scattered) const override;

        bool isTransparent() const override { return true; }

        double getTransparency() const override { return _transparency; };

        private:
        /// @brief Transparency of the glass
        double _transparency;

        /// @brief refrative index of the glass
        double _refractiveIndex;
    };
}  // namespace RayTracer