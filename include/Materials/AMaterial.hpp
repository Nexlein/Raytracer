/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** AMaterial
*/

#pragma once

#include "IMaterial.hpp"

namespace RayTracer {
    struct HitRecord;

    class AMaterial : public IMaterial {
        public:
        virtual ~AMaterial() = default;

        virtual bool isTransparent() const { return false; }

        [[nodiscard]] inline std::string getName() const { return _name; }

        [[nodiscard]] inline Math::Vector3D<double> getColor() const { return _color; }

        inline void setColor(const Math::Vector3D<double>& color) { _color = color; }

        virtual double getTransparency() const { return 0.0; };
    };
}  // namespace RayTracer