/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Vector3D
*/

/// @file Vector3D.cpp
/// @brief Implementation of the Vector3D class.

#include "Vector3D.hpp"

#include <cmath>

#include "RayTracerException.hpp"

template <typename T>
Math::Vector3D<T>::Vector3D(T x, T y, T z) : _x(x), _y(y), _z(z)
{
}

template <typename T>
T Math::Vector3D<T>::length() const
{
    return std::sqrt(_x * _x + _y * _y + _z * _z);
}

template <typename T>
T Math::Vector3D<T>::dot(const Vector3D<T>& other) const
{
    return _x * other._x + _y * other._y + _z * other._z;
}

template <typename T>
void Math::Vector3D<T>::rotateX(double angle)
{
    double radians = angle * (std::acos(-1.0) / 180.0);
    double cos_a = std::cos(radians);
    double sin_a = std::sin(radians);
    T old_y = _y;
    _y = old_y * cos_a - _z * sin_a;
    _z = old_y * sin_a + _z * cos_a;
}

template <typename T>
void Math::Vector3D<T>::rotateY(double angle)
{
    double radians = angle * (std::acos(-1.0) / 180.0);
    double cos_a = std::cos(radians);
    double sin_a = std::sin(radians);
    T old_x = _x;
    _x = old_x * cos_a + _z * sin_a;
    _z = -old_x * sin_a + _z * cos_a;
}

template <typename T>
void Math::Vector3D<T>::rotateZ(double angle)
{
    double radians = angle * (std::acos(-1.0) / 180.0);
    double cos_a = std::cos(radians);
    double sin_a = std::sin(radians);
    T old_x = _x;
    _x = old_x * cos_a - _y * sin_a;
    _y = old_x * sin_a + _y * cos_a;
}

// Operator with vector

template <typename T>
Math::Vector3D<T> Math::Vector3D<T>::operator+(const Vector3D<T>& other) const
{
    return Math::Vector3D<T>(_x + other._x, _y + other._y, _z + other._z);
}

template <typename T>
Math::Vector3D<T> Math::Vector3D<T>::operator-(const Vector3D<T>& other) const
{
    return Math::Vector3D<T>(_x - other._x, _y - other._y, _z - other._z);
}

template <typename T>
Math::Vector3D<T> Math::Vector3D<T>::operator*(const Vector3D<T>& other) const
{
    return Math::Vector3D<T>(_x * other._x, _y * other._y, _z * other._z);
}

template <typename T>
Math::Vector3D<T> Math::Vector3D<T>::operator/(const Vector3D<T>& other) const
{
    if (other._x == 0 || other._y == 0 || other._z == 0)
        throw RayTracer::RayTracerException("Vector3D: Division by zero (vector).");
    return Math::Vector3D<T>(_x / other._x, _y / other._y, _z / other._z);
}

// Operator ...= with vector

template <typename T>
Math::Vector3D<T>& Math::Vector3D<T>::operator+=(const Vector3D<T>& other)
{
    _x += other._x;
    _y += other._y;
    _z += other._z;
    return *this;
}

template <typename T>
Math::Vector3D<T>& Math::Vector3D<T>::operator-=(const Vector3D<T>& other)
{
    _x -= other._x;
    _y -= other._y;
    _z -= other._z;
    return *this;
}

template <typename T>
Math::Vector3D<T>& Math::Vector3D<T>::operator*=(const Vector3D<T>& other)
{
    _x *= other._x;
    _y *= other._y;
    _z *= other._z;
    return *this;
}

template <typename T>
Math::Vector3D<T>& Math::Vector3D<T>::operator/=(const Vector3D<T>& other)
{
    if (other._x == 0 || other._y == 0 || other._z == 0)
        throw RayTracer::RayTracerException("Vector3D: Division by zero (vector).");
    _x /= other._x;
    _y /= other._y;
    _z /= other._z;
    return *this;
}

// Operator with scalar

template <typename T>
Math::Vector3D<T> Math::Vector3D<T>::operator+(T scalar) const
{
    return Math::Vector3D<T>(_x + scalar, _y + scalar, _z + scalar);
}

template <typename T>
Math::Vector3D<T> Math::Vector3D<T>::operator-(T scalar) const
{
    return Math::Vector3D<T>(_x - scalar, _y - scalar, _z - scalar);
}

template <typename T>
Math::Vector3D<T> Math::Vector3D<T>::operator*(T scalar) const
{
    return Math::Vector3D<T>(_x * scalar, _y * scalar, _z * scalar);
}

template <typename T>
Math::Vector3D<T> Math::Vector3D<T>::operator/(T scalar) const
{
    if (scalar == 0) throw RayTracer::RayTracerException("Vector3D: Division by zero (scalar).");
    return Math::Vector3D<T>(_x / scalar, _y / scalar, _z / scalar);
}

// Operator ...= with scalar

template <typename T>
Math::Vector3D<T>& Math::Vector3D<T>::operator+=(T scalar)
{
    _x += scalar;
    _y += scalar;
    _z += scalar;
    return *this;
}

template <typename T>
Math::Vector3D<T>& Math::Vector3D<T>::operator-=(T scalar)
{
    _x -= scalar;
    _y -= scalar;
    _z -= scalar;
    return *this;
}

template <typename T>
Math::Vector3D<T>& Math::Vector3D<T>::operator*=(T scalar)
{
    _x *= scalar;
    _y *= scalar;
    _z *= scalar;
    return *this;
}

template <typename T>
Math::Vector3D<T>& Math::Vector3D<T>::operator/=(T scalar)
{
    if (scalar == 0) throw RayTracer::RayTracerException("Vector3D: Division by zero (scalar).");
    _x /= scalar;
    _y /= scalar;
    _z /= scalar;
    return *this;
}

template class Math::Vector3D<double>;
template class Math::Vector3D<float>;
template class Math::Vector3D<int>;
