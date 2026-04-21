/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** SceneParser
*/

#include "SceneParser.hpp"

#include "Point3D.hpp"
#include "PrimitiveFactory.hpp"
#include "RayTracerException.hpp"
#include "Vector3D.hpp"

RayTracer::SceneData RayTracer::SceneParser::parse(const std::string& filePath)
{
    try {
        libconfig::Config cfg;
        cfg.readFile(filePath.c_str());

        const libconfig::Setting& root = cfg.getRoot();

        int width = root["camera"]["resolution"]["width"];
        int height = root["camera"]["resolution"]["height"];

        double camX = root["camera"]["position"]["x"];
        double camY = root["camera"]["position"]["y"];
        double camZ = root["camera"]["position"]["z"];

        double rotX = root["camera"]["rotation"]["x"];
        double rotY = root["camera"]["rotation"]["y"];
        double rotZ = root["camera"]["rotation"]["z"];

        double fov = root["camera"]["fieldOfView"];

        Camera cam(Math::Point3D(camX, camY, camZ), Math::Vector3D(rotX, rotY, rotZ), width, height,
                   fov);

        std::vector<std::unique_ptr<IPrimitive>> primitives;
        const libconfig::Setting& spheres = root["primitives"]["spheres"];
        PrimitiveFactory factory;

        for (int i = 0; i < spheres.getLength(); i++)
            primitives.push_back(factory.createSphere(spheres[i]));

        return SceneData{std::move(cam), std::move(primitives), width, height};

    } catch (const libconfig::FileIOException& fioex) {
        throw RayTracerException("I/O error while reading file: " + filePath);
    } catch (const libconfig::ParseException& pex) {
        std::string file = pex.getFile() ? pex.getFile() : "unknown file";
        throw RayTracerException("Parse error at " + file + ":" + std::to_string(pex.getLine()) +
                                 " - " + pex.getError());
    } catch (const libconfig::SettingNotFoundException& nfex) {
        throw RayTracerException("Missing setting in configuration file: " +
                                 std::string(nfex.getPath()));
    }
}