/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** IMaterial
*/

#pragma once

#include <libconfig.h++>

#include "Ray.hpp"
#include "Vector3D.hpp"

namespace RayTracer {
    struct HitRecord;

    class IMaterial {
        public:
        virtual ~IMaterial() = default;

        /// @brief Initializes the material with settings from a configuration file
        /// @param setting The configuration settings for the given material
        virtual void init(const libconfig::Setting& setting) = 0;

        /// @brief computes the scattered ray and attenuation for a given ray and hit record
        /// @param rayIn Incoming ray that hits the material
        /// @param rec Hit record for the intersection
        /// @param attenuation Output parameter for the attenuation (color reduction) of the
        /// scattered ray
        /// @param scattered Output parameter for the scattered ray
        /// @return True if the ray was scattered, false otherwise
        virtual bool scatter(const Ray& rayIn, const HitRecord& rec,
                             Math::Vector3D<double>& attenuation, Ray& scattered) const = 0;

        /// @brief returns the name of the material
        /// @return The name of the material
        [[nodiscard]] inline std::string getName() const { return _name; }

        /// @brief returns the color of the material
        /// @return the color of the material
        [[nodiscard]] inline Math::Vector3D<double> getColor() const { return _color; }

        inline void setColor(const Math::Vector3D<double>& color) { _color = color; }

        protected:
        /// @brief Name of the material
        std::string _name;

        /// @brief Color of the lambertian material
        Math::Vector3D<double> _color;
    };
}  // namespace RayTracer
