/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Transparency
*/

#include "Transparency.hpp"

#include "ConfigUtils.hpp"

RayTracer::Transparency::Transparency(std::string name, Math::Vector3D<double> color, double transparency, double refractiveIndex)
    : _transparency(transparency), _refractiveIndex(refractiveIndex)
{
    _name = name;
    _color = color;
}

void RayTracer::Transparency::init(const libconfig::Setting& setting)
{
    // double transparency = 0.0;
    // double refractiveIndex = 0.0;
    (void)setting;
    return;
}