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

        bool isRefractive() const override { return false; }

        [[nodiscard]] inline std::string getName() const override { return _name; }

        [[nodiscard]] inline Math::Vector3D<double> getColor(
            [[maybe_unused]] double u = 0.0, [[maybe_unused]] double v = 0.0) const override
        {
            return _color;
        }

        void setColor(const Math::Vector3D<double>& color) override { _color = color; }

        virtual bool isRefractive() const { return false; }

        virtual double getRefractive() const { return 0.0; };

        virtual bool isReflective() const { return false; };

        virtual double getReflective() const { return 0.0; };
    };
}  // namespace RayTracer
