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

    /// @brief Parsed sphere description extracted from the scene file
    struct SphereData {
        /// @brief Center of the sphere in 3D space
        Math::Point3D<double> center;
        /// @brief Radius of the sphere
        double radius;
        /// @brief Color of the sphere, used for rendering
        Math::Vector3D<double> color;
    };

    struct PlaneData {
        /// @brief Axis along which the plane is oriented (X, Y, or Z)
        std::string axis;
        /// @brief Position of the plane along the specified axis
        int position;
        /// @brief Color of the plane, used for rendering
        Math::Vector3D<double> color;
    };

    /// @brief SceneParser class responsible for parsing scene files
    class SceneParser {
        public:
        /// @brief Parses a scene file and returns the scene data
        /// @param filePath The path to the scene file
        /// @return The parsed scene data
        SceneData parse(const std::string& filePath);

        private:
        /// @brief Parses all sphere definitions from the configuration file
        /// @param spheres The libconfig array containing sphere definitions
        /// @return The parsed sphere data
        std::vector<SphereData> parseSpheres(const libconfig::Setting& spheres);

        /// @brief Parses all plane definitions from the configuration file
        /// @param planes The libconfig array containing plane definitions
        /// @return The parsed plane data
        std::vector<PlaneData> parsePlanes(const libconfig::Setting& planes);

        /// @brief Helper function to extract a double value from a libconfig setting
        /// @param setting The libconfig setting to extract the value from
        /// @param key The key of the value to extract
        /// @param value The variable to store the extracted value
        /// @return True if the value was successfully extracted, false otherwise
        bool getAsDouble(const libconfig::Setting& setting, const char* key, double& value);
    };
}  // namespace RayTracer
