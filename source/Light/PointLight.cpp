/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** PointLight - Light source emitting from a specific position (implementation)
*/

#include "PointLight.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <memory>

#include "ConfigUtils.hpp"

extern "C" {
RayTracer::ILight* entryPoint() { return new RayTracer::PointLight(); }
}
