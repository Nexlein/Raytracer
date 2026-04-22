/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Point3D
*/

/// @file Point3D.cpp
/// @brief Implementation of the Point3D class.

#include "Point3D.hpp"

template <typename T>
Math::Point3D<T>::Point3D(T x, T y, T z) : _x(x), _y(y), _z(z)
{
}

// Operators

template <typename T>
Math::Point3D<T> Math::Point3D<T>::operator+(const Vector3D<T>& other) const
{
    return Math::Point3D<T>(_x + other._x, _y + other._y, _z + other._z);
}

template <typename T>
Math::Point3D<T> Math::Point3D<T>::operator-(const Vector3D<T>& other) const
{
    return Math::Point3D<T>(_x - other._x, _y - other._y, _z - other._z);
}

template <typename T>
Math::Vector3D<T> Math::Point3D<T>::operator-(const Point3D<T>& other) const
{
    return Math::Vector3D<T>(_x - other._x, _y - other._y, _z - other._z);
}

template <typename T>
T Math::Point3D<T>::dot(const Vector3D<T>& other) const
{
    return _x * other._x + _y * other._y + _z * other._z;
}

template <typename T>
void Math::Point3D<T>::translate(const Vector3D<T>& v)
{
    _x += v._x;
    _y += v._y;
    _z += v._z;
}

template class Math::Point3D<double>;
template class Math::Point3D<float>;
template class Math::Point3D<int>;
