/*
** EPITECH PROJECT, 2026
** G-OOP-400-MPL-4-1-bsraytracer-11
** File description:
** RayTracerException
*/

#pragma once

#include <exception>
#include <string>

namespace RayTracer {
    class RayTracerException : public std::exception {
        public:
        RayTracerException(const std::string& message);

        [[nodiscard]] const char* what() const noexcept override;

        private:
        std::string _message;
    };
}  // namespace RayTracer
