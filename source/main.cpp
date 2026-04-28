/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** main
*/

/// @file main.cpp
/// @brief Main entry point for the Ray Tracer application

#include <iostream>
#include <memory>
#include <vector>

#include "Core/Camera.hpp"
#include "Core/Renderer.hpp"
#include "Core/SceneParser.hpp"
#include "Exceptions/RayTracerException.hpp"
#include "Primitives/IPrimitive.hpp"

/// @brief Usage message
const std::string USAGE_MESSAGE =
    "USAGE: ./raytracer <SCENE_FILE>\n"
    "  SCENE_FILE: scene configuration\n";

/// @brief Output filename
const std::string OUTPUT_FILENAME = "output.ppm";

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cerr << USAGE_MESSAGE;
        return 84;
    }

    if (std::string(argv[1]) == "--help" || std::string(argv[1]) == "-h") {
        std::cerr << USAGE_MESSAGE;
        return 0;
    }

    try {
        RayTracer::SceneParser parser;
        RayTracer::SceneData sceneData = parser.parse(argv[1]);

        RayTracer::Renderer renderer = std::move(sceneData.renderer);
        renderer.render(sceneData.camera, sceneData.primitives, sceneData.lights, OUTPUT_FILENAME);

    } catch (const RayTracer::RayTracerException& e) {
        std::cerr << "RayTracer Error: " << e.what() << std::endl;
        return 84;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 84;
    }

    return 0;
}
