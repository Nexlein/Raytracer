/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** SceneParser
*/

#include "SceneParser.hpp"

#include "AmbientLight.hpp"
#include "ConfigUtils.hpp"
#include "PluginFactory.hpp"
#include "Point3D.hpp"
#include "RayTracerException.hpp"
#include "Vector3D.hpp"

void RayTracer::SceneParser::parseAmbientLight(std::vector<std::unique_ptr<ILight>>& lights,
                                               const libconfig::Setting& lightSetting)
{
    lights.push_back(
        PluginFactory<ILight>::create("./plugins/raytracer_ambientlight.so", lightSetting));
}

void RayTracer::SceneParser::parseDirectionalLights(std::vector<std::unique_ptr<ILight>>& lights,
                                                    const libconfig::Setting& lightSetting)
{
    if (lightSetting.exists("directional")) {
        const libconfig::Setting& directionalLights = lightSetting["directional"];

        for (int i = 0; i < directionalLights.getLength(); i++) {
            lights.push_back(PluginFactory<ILight>::create(
                "./plugins/raytracer_directionallight.so", directionalLights[i]));
        }
    }
}

RayTracer::SceneData RayTracer::SceneParser::parse(const std::string& filePath)
{
    try {
        libconfig::Config cfg;
        cfg.readFile(filePath.c_str());

        const libconfig::Setting& root = cfg.getRoot();

        if (!root.exists("camera"))
            throw RayTracerException("SceneParser: Missing camera configuration.");

        Camera cam;
        cam.init(root["camera"]);

        int width = root["camera"]["resolution"]["width"];
        int height = root["camera"]["resolution"]["height"];

        std::vector<std::unique_ptr<IPrimitive>> primitives;
        std::vector<std::unique_ptr<ILight>> lights;

        if (root.exists("primitives")) {
            const libconfig::Setting& primitivesSetting = root["primitives"];

            for (int i = 0; i < primitivesSetting.getLength(); ++i) {
                const libconfig::Setting& listSetting = primitivesSetting[i];
                std::string typeName = listSetting.getName();

                for (int j = 0; j < listSetting.getLength(); ++j) {
                    std::string pluginPath = "./plugins/raytracer_" + typeName + ".so";
                    primitives.push_back(
                        PluginFactory<IPrimitive>::create(pluginPath, listSetting[j]));
                }
            }
        }

        if (root.exists("lights")) {
            const libconfig::Setting& lightSetting = root["lights"];

            if (lightSetting.exists("ambient")) parseAmbientLight(lights, lightSetting);
            if (lightSetting.exists("directional")) parseDirectionalLights(lights, lightSetting);
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
