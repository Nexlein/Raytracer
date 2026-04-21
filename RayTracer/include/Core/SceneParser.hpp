/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** SceneParser
*/

/// @file SceneParser.hpp
/// @brief SceneParser class for parsing scene files

#pragma once

#include <libconfig.h++>
#include <memory>
#include <string>
#include <vector>

#include "Camera.hpp"
#include "IPrimitive.hpp"

/// @brief Namespace for the Ray Tracer project
namespace RayTracer {
    /// @brief Struct to hold the parsed scene data
    struct SceneData {
        /// @brief Camera object representing the camera in the scene
        Camera camera;
        /// @brief List of primitives in the scene
        std::vector<std::unique_ptr<IPrimitive>> primitives;
        /// @brief Width of the output image
        int width;
        /// @brief Height of the output image
        int height;
    };

    /// @brief SceneParser class responsible for parsing scene files
    class SceneParser {
        public:
        /// @brief Parses a scene file and returns the scene data
        /// @param filePath The path to the scene file
        /// @return The parsed scene data
        SceneData parse(const std::string& filePath);
    };

}  // namespace RayTracer
