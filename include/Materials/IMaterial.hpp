/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** IMaterial
*/

#pragma once

#include <libconfig.h++>

namespace RayTracer {
    class IMaterial {
        public:
        virtual ~IMaterial() = default;

        /// @brief Initializes the material with settings from a configuration file
        /// @param setting The configuration settings for the given material
        virtual void init(const libconfig::Setting& setting) = 0;

        protected:
        /// @brief Name of the material
        std::string _name;
    };
} // namespace Raytracer
