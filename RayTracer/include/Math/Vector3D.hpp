/*
** EPITECH PROJECT, 2026
** BSRaytracer
** File description:
** Vector3D
*/

#pragma once

namespace Math {
    template <typename T = double>
    class Vector3D {
        public:
        Vector3D(T x = T{}, T y = T{}, T z = T{});

        T _x;
        T _y;
        T _z;

        [[nodiscard]] T length() const;
        [[nodiscard]] T dot(const Vector3D& other) const;

        void rotateX(double angle);
        void rotateY(double angle);
        void rotateZ(double angle);

        // Operator with vector

        [[nodiscard]] Vector3D operator+(const Vector3D& other) const;
        [[nodiscard]] Vector3D operator-(const Vector3D& other) const;
        [[nodiscard]] Vector3D operator*(const Vector3D& other) const;
        [[nodiscard]] Vector3D operator/(const Vector3D& other) const;

        // Operator ...= with vector

        [[nodiscard]] Vector3D& operator+=(const Vector3D& other);
        [[nodiscard]] Vector3D& operator-=(const Vector3D& other);
        [[nodiscard]] Vector3D& operator*=(const Vector3D& other);
        [[nodiscard]] Vector3D& operator/=(const Vector3D& other);

        // Operator with scalar

        [[nodiscard]] Vector3D operator+(T scalar) const;
        [[nodiscard]] Vector3D operator-(T scalar) const;
        [[nodiscard]] Vector3D operator*(T scalar) const;
        [[nodiscard]] Vector3D operator/(T scalar) const;

        // Operator ...= with scalar

        [[nodiscard]] Vector3D& operator+=(T scalar);
        [[nodiscard]] Vector3D& operator-=(T scalar);
        [[nodiscard]] Vector3D& operator*=(T scalar);
        [[nodiscard]] Vector3D& operator/=(T scalar);
    };
}  // namespace Math
