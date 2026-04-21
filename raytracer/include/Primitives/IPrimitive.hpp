/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** IPrimitive
*/

#pragma once

#include "Ray.hpp"

namespace RayTracer {
    class IPrimitive {
        public:
        virtual ~IPrimitive() = default;

        [[nodiscard]] virtual bool hits(const Ray& ray) const = 0;
    };
}  // namespace RayTracer
