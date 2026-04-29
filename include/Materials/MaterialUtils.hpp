/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** f
*/

#include <algorithm>

#include "Vector3D.hpp"

namespace RayTracer {
    class MaterialUtils {
        public:
        static double randomDouble() { return rand() / (RAND_MAX + 1.0); }

        static double schlick(double cosine, double ior)
        {
            double r0 = (1 - ior) / (1 + ior);
            r0 = r0 * r0;
            return r0 + (1 - r0) * std::pow(1 - cosine, 5);
        }

        static Math::Vector3D<double> reflect(const Math::Vector3D<double>& v,
                                              const Math::Vector3D<double>& n)
        {
            return v - n * 2.0 * v.dot(n);
        }

        static Math::Vector3D<double> refract(const Math::Vector3D<double>& uv,
                                              const Math::Vector3D<double>& n, double ratio)
        {
            double cosTheta = std::min<double>((-uv).dot(n), 1.0);
            Math::Vector3D<double> rPerp = (uv + n * cosTheta) * ratio;
            Math::Vector3D<double> rParallel = n * -std::sqrt(std::abs(1.0 - rPerp.dot(rPerp)));
            return rPerp + rParallel;
        }

        static Math::Vector3D<double> randomUnitVector()
        {
            double a = randomDouble() * 2.0 * M_PI;
            double z = randomDouble() * 2.0 - 1.0;
            double r = std::sqrt(1.0 - z * z);
            return {r * std::cos(a), r * std::sin(a), z};
        }
    };
}  // namespace RayTracer