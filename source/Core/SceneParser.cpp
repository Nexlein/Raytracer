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

#include "DirectionalLight.hpp"
#include "AmbientLight.hpp"

bool RayTracer::SceneParser::getAsDouble(const libconfig::Setting& setting, const char* key,
                                         double& value)
{
    int intValue = 0;
    if (setting.lookupValue(key, intValue)) {
        value = static_cast<double>(intValue);
        return true;
    }

    float floatValue = 0.0f;
    if (setting.lookupValue(key, floatValue)) {
        value = static_cast<double>(floatValue);
        return true;
    }

    return setting.lookupValue(key, value);
}

Math::Vector3D<double> RayTracer::SceneParser::parseColor(
    const libconfig::Setting& primitiveSetting)
{
    if (!primitiveSetting.exists("color"))
        throw RayTracerException("SceneParser: Missing color parameter for primitive.");

    const libconfig::Setting& colorSetting = primitiveSetting["color"];

    int red = 0;
    int green = 0;
    int blue = 0;

    if (!colorSetting.lookupValue("r", red) || !colorSetting.lookupValue("g", green) ||
        !colorSetting.lookupValue("b", blue)) {
        throw RayTracerException(
            "SceneParser: Invalid or missing r, g, b values in color parameter.");
        }

    return Math::Vector3D<double>(red, green, blue);
}

void RayTracer::SceneParser::parseAmbientLight(
    std::vector<std::unique_ptr<ILight>>& lights,
    const libconfig::Setting& lightSetting)
{
    double ambientIntensity = 0.0;
    getAsDouble(lightSetting, "ambient", ambientIntensity);

    Vector3D color = {255.0, 255.0, 255.0};
    if (lightSetting.exists("color")) {
        const libconfig::Setting& colorSetting = lightSetting["color"];
        int red = 0;
        int green = 0;
        int blue = 0;

        if (!colorSetting.lookupValue("r", red) || !colorSetting.lookupValue("g", green) ||
            !colorSetting.lookupValue("b", blue)) {
            throw RayTracerException(
                "SceneParser: Invalid or missing r, g, b values in directional light color.");
        }
        color = Math::Vector3D<double>(red, green, blue);
    }
    if (ambientIntensity > 0.0)
        lights.push_back(std::make_unique<AmbientLight>(ambientIntensity, color));
}

void RayTracer::SceneParser::parseDirectionalLights(
    std::vector<std::unique_ptr<ILight>>& lights,
    const libconfig::Setting& lightSetting)
{
    double diffuse = 0.0;

    getAsDouble(lightSetting, "diffuse", diffuse);
    if (lightSetting.exists("directional") && diffuse > 0.0) {
        const libconfig::Setting& directionalLights = lightSetting["directional"];

        for (int i = 0; i < directionalLights.getLength(); i++) {
            if (!directionalLights[i].exists("direction"))
                throw RayTracerException("SceneParser: Missing parameters for directional light.");

            const libconfig::Setting& directionSetting = directionalLights[i]["direction"];
            double x = 0.0;
            double y = 0.0;
            double z = 0.0;
            Vector3D color = {255.0, 255.0, 255.0};

            if (directionalLights[i].exists("color")) {
                const libconfig::Setting& colorSetting = directionalLights[i]["color"];
                int red = 0;
                int green = 0;
                int blue = 0;

                if (!colorSetting.lookupValue("r", red) || !colorSetting.lookupValue("g", green) ||
                    !colorSetting.lookupValue("b", blue)) {
                    throw RayTracerException(
                        "SceneParser: Invalid or missing r, g, b values in directional light color.");
                }
                color = Math::Vector3D<double>(red, green, blue);
            }
            if (!getAsDouble(directionSetting, "x", x) ||
                !getAsDouble(directionSetting, "y", y) ||
                !getAsDouble(directionSetting, "z", z))
                throw RayTracerException("SceneParser: Missing parameters for directional light.");

            lights.push_back(std::make_unique<DirectionalLight>(Math::Vector3D<double>(x, y, z), diffuse, color));
        }
    }
}

std::vector<RayTracer::SphereData> RayTracer::SceneParser::parseSpheres(
    const libconfig::Setting& spheres)
{
    std::vector<SphereData> parsedSpheres;

    for (int i = 0; i < spheres.getLength(); i++) {
        const libconfig::Setting& sphereSetting = spheres[i];
        double x = 0.0;
        double y = 0.0;
        double z = 0.0;
        double radius = 0.0;

        if (!getAsDouble(sphereSetting, "x", x) || !getAsDouble(sphereSetting, "y", y) ||
            !getAsDouble(sphereSetting, "z", z) || !getAsDouble(sphereSetting, "r", radius)) {
            throw RayTracerException("SceneParser: Missing parameters for sphere.");
        }

        parsedSpheres.push_back(
            SphereData{Math::Point3D<double>(x, y, z), radius, parseColor(sphereSetting)});
    }

    return parsedSpheres;
}

std::vector<RayTracer::PlaneData> RayTracer::SceneParser::parsePlanes(
    const libconfig::Setting& planes)
{
    std::vector<PlaneData> parsedPlanes;

    for (int i = 0; i < planes.getLength(); i++) {
        const libconfig::Setting& planeSetting = planes[i];
        std::string axis;
        double position = 0.0;

        if (!planeSetting.lookupValue("axis", axis) ||
            !getAsDouble(planeSetting, "position", position)) {
            throw RayTracerException("SceneParser: Missing parameters for plane.");
        }

        parsedPlanes.push_back(
            PlaneData{axis, static_cast<int>(position), parseColor(planeSetting)});
    }

    return parsedPlanes;
}

RayTracer::SceneData RayTracer::SceneParser::parse(const std::string& filePath)
{
    try {
        libconfig::Config cfg;
        cfg.readFile(filePath.c_str());

        const libconfig::Setting& root = cfg.getRoot();

        int width = root["camera"]["resolution"]["width"];
        int height = root["camera"]["resolution"]["height"];

        const libconfig::Setting& cameraSetting = root["camera"];
        const libconfig::Setting& positionSetting = cameraSetting["position"];
        const libconfig::Setting& rotationSetting = cameraSetting["rotation"];

        double camX = 0.0;
        double camY = 0.0;
        double camZ = 0.0;
        double rotX = 0.0;
        double rotY = 0.0;
        double rotZ = 0.0;
        double fov = 0.0;

        if (!getAsDouble(positionSetting, "x", camX) || !getAsDouble(positionSetting, "y", camY) ||
            !getAsDouble(positionSetting, "z", camZ) || !getAsDouble(rotationSetting, "x", rotX) ||
            !getAsDouble(rotationSetting, "y", rotY) || !getAsDouble(rotationSetting, "z", rotZ) ||
            !getAsDouble(cameraSetting, "fieldOfView", fov)) {
            throw RayTracerException("SceneParser: Missing parameters for camera.");
        }

        Camera cam(Math::Point3D(camX, camY, camZ), Math::Vector3D(rotX, rotY, rotZ), width, height,
                   fov);

        std::vector<std::unique_ptr<IPrimitive>> primitives;
        std::vector<std::unique_ptr<ILight>> lights;
        PrimitiveFactory factory;

        if (root.exists("primitives")) {
            const libconfig::Setting& primitivesSetting = root["primitives"];

            if (primitivesSetting.exists("spheres")) {
                const libconfig::Setting& spheres = primitivesSetting["spheres"];
                const std::vector<SphereData> parsedSpheres = parseSpheres(spheres);

                for (const SphereData& sphere : parsedSpheres)
                    primitives.push_back(factory.createSphere(sphere));
            }

            if (primitivesSetting.exists("planes")) {
                const libconfig::Setting& planes = primitivesSetting["planes"];
                const std::vector<PlaneData> parsedPlanes = parsePlanes(planes);

                for (const PlaneData& plane : parsedPlanes)
                    primitives.push_back(factory.createPlane(plane));
            }
        }

        if (root.exists("lights")) {
            const libconfig::Setting& lightSetting = root["lights"];

            parseAmbientLight(lights, lightSetting);
            parseDirectionalLights(lights, lightSetting);
        }
        return SceneData{std::move(cam), std::move(primitives), std::move(lights), width, height};

    } catch (const libconfig::FileIOException& fioex) {
        throw RayTracerException("I/O error while reading file: " + filePath);
    } catch (const libconfig::ParseException& pex) {
        std::string file = pex.getFile() ? pex.getFile() : "unknown file";
        throw RayTracerException("Parse error at " + file + ":" + std::to_string(pex.getLine()) +
                                 " - " + pex.getError());
    } catch (const libconfig::SettingNotFoundException& nfex) {
        throw RayTracerException("Missing setting in configuration file: " +
                                 std::string(nfex.getPath()));
    } catch (const libconfig::SettingTypeException& stex) {
        throw RayTracerException("Invalid setting type in configuration file: " +
                                 std::string(stex.getPath()));
    }
}
