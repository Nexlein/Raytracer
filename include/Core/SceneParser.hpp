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
#include "ILight.hpp"
#include "IPrimitive.hpp"
#include "Renderer.hpp"

/// @brief Namespace for the Ray Tracer project
namespace RayTracer {
    /// @brief Struct to hold the parsed scene data
    struct SceneData {
        /// @brief Camera object representing the camera in the scene
        Camera camera;
        /// @brief Renderer object representing the renderer configuration
        Renderer renderer;
        /// @brief List of primitives in the scene
        std::vector<std::unique_ptr<IPrimitive>> primitives;
        /// @brief List of lights in the scene
        std::vector<std::unique_ptr<ILight>> lights;
    };

    /// @brief SceneParser class responsible for parsing scene files
    class SceneParser {
        public:
        /// @brief Parses a scene file and returns the scene data
        /// @param filePath The path to the scene file
        /// @return The parsed scene data
        SceneData parse(const std::string& filePath);

        private:
        /// @brief parses an ambient light definition from the configuration file and adds it to the
        /// list of lights
        /// @param lights list of lights to which the parsed ambient light will be added
        /// @param lightSetting libconfig setting containing the ambient light definition
        void parseAmbientLight(std::vector<std::unique_ptr<ILight>>& lights,
                               const libconfig::Setting& lightSetting);

        /// @brief parses a list of directional lights from the configuration file and adds them to
        /// the list of lights
        /// @param lights list of lights to which the parsed directional light will be added
        /// @param lightSetting libconfig setting containing the directional light definition
        void parseDirectionalLights(std::vector<std::unique_ptr<ILight>>& lights,
                                    const libconfig::Setting& lightSetting);
    };
}  // namespace RayTracer
