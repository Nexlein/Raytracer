/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** SceneParser
*/

#include "SceneParser.hpp"

#include <string>

#include "AmbientLight.hpp"
#include "ConfigUtils.hpp"
#include "PluginFactory.hpp"
#include "Point3D.hpp"
#include "RayTracerException.hpp"
#include "Vector3D.hpp"

void RayTracer::SceneParser::setMaterialstoPrimitives(
    std::vector<std::unique_ptr<IPrimitive>>& primitives,
    const std::map<std::string, std::shared_ptr<IMaterial>>& materials)
{
    for (auto& primitive : primitives) {
        if (!primitive->getMaterialName().empty()) {
            auto it = materials.find(primitive->getMaterialName());
            if (it != materials.end())
                primitive->setMaterial(it->second);
            else
                throw RayTracerException("SceneParser: Material '" + primitive->getMaterialName() +
                                         "' not found for primitive.");
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
        if (!root.exists("renderer"))
            throw RayTracerException("SceneParser: Missing renderer configuration.");

        Camera cam;
        cam.init(root["camera"]);

        Renderer renderer;
        renderer.init(root["renderer"]);

        std::map<std::string, std::shared_ptr<IMaterial>> materials;
        std::vector<std::unique_ptr<IPrimitive>> primitives;
        std::vector<std::unique_ptr<ILight>> lights;

        if (root.exists("materials")) {
            const libconfig::Setting& materialsSetting = root["materials"];

            for (int i = 0; i < materialsSetting.getLength(); ++i) {
                const libconfig::Setting& mat = materialsSetting[i];
                std::string typeName = mat.getName();

                for (int j = 0; j < mat.getLength(); ++j) {
                    std::string pluginPath = "./plugins/raytracer_" + typeName + ".so";
                    materials[std::string(mat[j]["name"])] =
                        PluginFactory<IMaterial>::create(pluginPath, mat[j]);
                }
            }
        }

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
            const libconfig::Setting& lightsSetting = root["lights"];

            for (int i = 0; i < lightsSetting.getLength(); ++i) {
                const libconfig::Setting& lightSetting = lightsSetting[i];
                std::string typeName = lightSetting.getName();

                if (lightSetting.isList() || lightSetting.isArray() || lightSetting.isGroup()) {
                    for (int j = 0; j < lightSetting.getLength(); ++j) {
                        std::string pluginPath = "./plugins/raytracer_" + typeName + ".so";
                        lights.push_back(
                            PluginFactory<ILight>::create(pluginPath, lightSetting[j]));
                    }
                } else {
                    std::string pluginPath = "./plugins/raytracer_" + typeName + ".so";
                    lights.push_back(PluginFactory<ILight>::create(pluginPath, lightsSetting));
                }
            }
        }
        setMaterialstoPrimitives(primitives, materials);

        if (!renderer.getBackgroundMaterialName().empty()) {
            auto it = materials.find(renderer.getBackgroundMaterialName());
            if (it != materials.end())
                renderer.setBackgroundMaterial(it->second);
            else
                throw RayTracerException("SceneParser: Background Material '" +
                                         renderer.getBackgroundMaterialName() + "' not found.");
        }

        return SceneData{std::move(cam), std::move(renderer), std::move(primitives),
                         std::move(lights), std::move(materials)};

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
