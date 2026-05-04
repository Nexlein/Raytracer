/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** Box.cpp
*/

#include "Box.hpp"

#include <cmath>
#include <memory>

#include "ConfigUtils.hpp"
#include "RayTracerException.hpp"

/// @brief Namespace for the RayTracer project
namespace RayTracer {

    bool Box::hits(const Ray& ray, HitRecord& rec) const
    {
        rec.material = _material.get();

        double txmin = (_min._x - ray._origin._x) / ray._direction._x;
        double txmax = (_max._x - ray._origin._x) / ray._direction._x;
        double tymin = (_min._y - ray._origin._y) / ray._direction._y;
        double tymax = (_max._y - ray._origin._y) / ray._direction._y;
        double tzmin = (_min._z - ray._origin._z) / ray._direction._z;
        double tzmax = (_max._z - ray._origin._z) / ray._direction._z;

        double txEntry = std::fmin(txmin, txmax);
        double tyEntry = std::fmin(tymin, tymax);
        double tzEntry = std::fmin(tzmin, tzmax);

        double tmin = std::fmax(std::fmax(txEntry, tyEntry), tzEntry);
        double tmax = std::fmin(
            std::fmin(
                std::fmax(txmin, txmax),
                std::fmax(tymin, tymax)
            ),
            std::fmax(tzmin, tzmax)
        );

        if (tmax <= tmin) return false;

        rec.distance = (tmin >= 0) ? tmin : tmax;
        if (rec.distance < 0) return false;

        Math::Vector3D<double> localNormal;
        if (tmin == txEntry)
            localNormal = (ray._direction._x < 0) ? Math::Vector3D<double>{1,0,0} :
                                                    Math::Vector3D<double>{-1,0,0};
        else if (tmin == tyEntry)
            localNormal = (ray._direction._y < 0) ? Math::Vector3D<double>{0,1,0} :
                                                    Math::Vector3D<double>{0,-1,0};
        else
            localNormal = (ray._direction._z < 0) ? Math::Vector3D<double>{0,0,1} :
                                                    Math::Vector3D<double>{0,0,-1};

        localNormal.rotateX(_rotation._x);
        localNormal.rotateY(_rotation._y);
        localNormal.rotateZ(_rotation._z);

        rec.normal = localNormal;
        rec.p = ray._origin + ray._direction * rec.distance;
        return true;
    }

    void Box::init(const libconfig::Setting& setting)
    {
        ConfigUtils::parsePoint3D(setting, "position", _min, true);

        ConfigUtils::parseVector3D(setting, "rotation", _rotation, false);

        ConfigUtils::parsePoint3D(setting, "dimension", _max, true);
        if (_max._x < 0 || _max._y < 0 || _max._z < 0)
            throw RayTracerException("Box's dimension cannot be negatives.");

        _max = {_max._x + _min._x, _max._y + _min._y, _max._z + _min._z };

        if (setting.exists("material")) {
            std::string name = setting["material"];
            _materialName = name;
        }
    }

    extern "C" {
    IPrimitive* entryPoint() { return new Box(); }
    }
}  // namespace RayTracer
