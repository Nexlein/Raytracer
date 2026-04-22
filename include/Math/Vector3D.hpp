/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Vector3D
*/

/// @file Vector3D.hpp
/// @brief Vector3D class definition

#pragma once

/// @brief Namespace for the Math library
namespace Math {
    /// @brief Represents a vector in 3D space
    /// @tparam T The type of the coordinates (default is double)
    template <typename T = double>
    class Vector3D {
        public:
        /// @brief Constructs a Vector3D object
        /// @param x The x-coordinate of the vector (default is 0)
        /// @param y The y-coordinate of the vector (default is 0)
        /// @param z The z-coordinate of the vector (default is 0)
        Vector3D(T x = T{}, T y = T{}, T z = T{});

        /// @brief The x-coordinate of the vector
        T _x;
        /// @brief The y-coordinate of the vector
        T _y;
        /// @brief The z-coordinate of the vector
        T _z;

        /// @brief Computes the length (magnitude) of the vector
        /// @return The length of the vector
        [[nodiscard]] T length() const;
        /// @brief Computes the dot product of this vector and another vector
        /// @param other The other vector
        /// @return The dot product
        [[nodiscard]] T dot(const Vector3D& other) const;

        /// @brief Rotates the vector around the X axis
        /// @param angle The angle of rotation in radians
        void rotateX(double angle);

        /// @brief Rotates the vector around the Y axis
        /// @param angle The angle of rotation in radians
        void rotateY(double angle);

        /// @brief Rotates the vector around the Z axis
        /// @param angle The angle of rotation in radians
        void rotateZ(double angle);

        // Operator with vector

        /// @brief Adds two vectors element-wise
        /// @param other The vector to add
        /// @return The resulting vector
        [[nodiscard]] Vector3D operator+(const Vector3D& other) const;

        /// @brief Subtracts a vector from this vector element-wise
        /// @param other The vector to subtract
        /// @return The resulting vector
        [[nodiscard]] Vector3D operator-(const Vector3D& other) const;

        /// @brief Multiplies two vectors element-wise
        /// @param other The vector to multiply
        /// @return The resulting vector
        [[nodiscard]] Vector3D operator*(const Vector3D& other) const;

        /// @brief Divides this vector by another vector element-wise
        /// @param other The vector to divide by
        /// @return The resulting vector
        [[nodiscard]] Vector3D operator/(const Vector3D& other) const;

        // Operator ...= with vector

        /// @brief Adds a vector to this vector element-wise
        /// @param other The vector to add
        /// @return Reference to the modified vector
        [[nodiscard]] Vector3D& operator+=(const Vector3D& other);

        /// @brief Subtracts a vector from this vector element-wise
        /// @param other The vector to subtract
        /// @return Reference to the modified vector
        [[nodiscard]] Vector3D& operator-=(const Vector3D& other);

        /// @brief Multiplies this vector by another vector element-wise
        /// @param other The vector to multiply
        /// @return Reference to the modified vector
        [[nodiscard]] Vector3D& operator*=(const Vector3D& other);

        /// @brief Divides this vector by another vector element-wise
        /// @param other The vector to divide by
        /// @return Reference to the modified vector
        [[nodiscard]] Vector3D& operator/=(const Vector3D& other);

        // Operator with scalar

        /// @brief Adds a scalar to each element of the vector
        /// @param scalar The scalar to add
        /// @return The resulting vector
        [[nodiscard]] Vector3D operator+(T scalar) const;

        /// @brief Subtracts a scalar from each element of the vector
        /// @param scalar The scalar to subtract
        /// @return The resulting vector
        [[nodiscard]] Vector3D operator-(T scalar) const;

        /// @brief Multiplies each element of the vector by a scalar
        /// @param scalar The scalar to multiply
        /// @return The resulting vector
        [[nodiscard]] Vector3D operator*(T scalar) const;

        /// @brief Divides each element of the vector by a scalar
        /// @param scalar The scalar to divide by
        /// @return The resulting vector
        [[nodiscard]] Vector3D operator/(T scalar) const;

        // Operator ...= with scalar

        /// @brief Adds a scalar to each element of this vector
        /// @param scalar The scalar to add
        /// @return Reference to the modified vector
        [[nodiscard]] Vector3D& operator+=(T scalar);

        /// @brief Subtracts a scalar from each element of this vector
        /// @param scalar The scalar to subtract
        /// @return Reference to the modified vector
        [[nodiscard]] Vector3D& operator-=(T scalar);

        /// @brief Multiplies each element of this vector by a scalar
        /// @param scalar The scalar to multiply
        /// @return Reference to the modified vector
        [[nodiscard]] Vector3D& operator*=(T scalar);

        /// @brief Divides each element of this vector by a scalar
        /// @param scalar The scalar to divide by
        /// @return Reference to the modified vector
        [[nodiscard]] Vector3D& operator/=(T scalar);
    };
}  // namespace Math
