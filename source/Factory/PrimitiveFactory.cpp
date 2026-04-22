/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** PrimitiveFactory
*/

#include "PrimitiveFactory.hpp"

#include "RayTracerException.hpp"
#include "Sphere.hpp"
#include "Plane.hpp"

std::unique_ptr<RayTracer::IPrimitive> RayTracer::PrimitiveFactory::createSphere(
    const libconfig::Setting& setting)
{
    double x = 0.0, y = 0.0, z = 0.0, r = 0.0;

    if (!setting.lookupValue("x", x) || !setting.lookupValue("y", y) ||
        !setting.lookupValue("z", z) || !setting.lookupValue("r", r)) {
        throw RayTracerException("PrimitiveFactory: Missing parameters for sphere.");
    }

    Math::Point3D<double> center(x, y, z);
    auto sphere = std::make_unique<Sphere>(center, r);

    if (!setting.exists("color"))
        throw RayTracerException("PrimitiveFactory: Missing color parameter for primitive.");

    const libconfig::Setting& colorSetting = setting["color"];

    int rCol = 0, gCol = 0, bCol = 0;
    if (!colorSetting.lookupValue("r", rCol) || !colorSetting.lookupValue("g", gCol) ||
        !colorSetting.lookupValue("b", bCol)) {
        throw RayTracerException(
            "PrimitiveFactory: Invalid or missing r, g, b values in color parameter.");
    }

    sphere->color = Math::Vector3D<double>(rCol, gCol, bCol);

    return sphere;
}

std::unique_ptr<RayTracer::IPrimitive> RayTracer::PrimitiveFactory::createPlane(
    const libconfig::Setting& setting)
{
    std::string axis;
    int position = 0;

    if (!setting.lookupValue("axis", axis) || !setting.lookupValue("position", position))
        throw RayTracerException("PrimitiveFactory: Missing parameters for plane.");

    auto plane = std::make_unique<Plane>(axis, position);

    if (!setting.exists("color"))
        throw RayTracerException("PrimitiveFactory: Missing color parameter for primitive.");

    const libconfig::Setting& colorSetting = setting["color"];

    int rCol = 0, gCol = 0, bCol = 0;
    if (!colorSetting.lookupValue("r", rCol) || !colorSetting.lookupValue("g", gCol) ||
        !colorSetting.lookupValue("b", bCol)) {
        throw RayTracerException(
            "PrimitiveFactory: Invalid or missing r, g, b values in color parameter.");
    }

    plane->color = Math::Vector3D<double>(rCol, gCol, bCol);

    return plane;
}
