/*
** EPITECH PROJECT, 2026
** G-OOP-400-MPL-4-1-bsraytracer-11
** File description:
** Point3D
*/

#pragma once

#include "Vector3D.hpp"

namespace Math {
    template <typename T = double>
    class Point3D {
        public:
        Point3D(T x = T{}, T y = T{}, T z = T{});

        T _x;
        T _y;
        T _z;

        // Operators
        [[nodiscard]] Point3D operator+(const Vector3D<T>& other) const;
        [[nodiscard]] Point3D operator-(const Vector3D<T>& other) const;
        [[nodiscard]] Math::Vector3D<T> operator-(const Point3D& other) const;

        void translate(const Vector3D<T>& v);
    };
}  // namespace Math
