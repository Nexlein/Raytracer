/*
** EPITECH PROJECT, 2026
** G-OOP-400-MPL-4-1-bsraytracer-11
** File description:
** RayTracerException
*/

#include "RayTracerException.hpp"

RayTracer::RayTracerException::RayTracerException(const std::string& message) : _message(message) {}

const char* RayTracer::RayTracerException::what() const noexcept { return _message.c_str(); }
