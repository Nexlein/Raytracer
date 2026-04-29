/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Triangle
*/

/// @file Triangle.cpp
/// @brief Implementation of the Triangle class.

#include "Triangle.hpp"

#include <cmath>
#include <memory>

#include "ConfigUtils.hpp"
#include "RayTracerException.hpp"

bool RayTracer::Triangle::hits(const Ray& ray, HitRecord& rec) const
{
    const double epsilon = 1e-6;

    // Calcul des arêtes
    Vector3D edge1 = _v1 - _v0;
    Vector3D edge2 = _v2 - _v0;

    Vector3D pvec(ray._direction._y * edge2._z - ray._direction._z * edge2._y,
                  ray._direction._z * edge2._x - ray._direction._x * edge2._z,
                  ray._direction._x * edge2._y - ray._direction._y * edge2._x);

    double det = edge1.dot(pvec);

    // "det" proche de 0 = rayon parallèle au triangle
    if (std::abs(det) < epsilon) return false;

    double invDet = 1.0 / det;

    Vector3D tvec = ray._origin - _v0;
    double u = tvec.dot(pvec) * invDet;

    // "u" en dehors du triangle
    if (u < 0.0 || u > 1.0) return false;

    Vector3D qvec(tvec._y * edge1._z - tvec._z * edge1._y, tvec._z * edge1._x - tvec._x * edge1._z,
                  tvec._x * edge1._y - tvec._y * edge1._x);
    double v = ray._direction.dot(qvec) * invDet;
    // "v" en dehors du triangle
    if (v < 0.0 || u + v > 1.0) return false;

    double t = edge2.dot(qvec) * invDet;

    // Vérifie que l'intersection est devant la caméra
    if (t <= epsilon) return false;

    // Remplir le HitRecord
    rec.distance = t;
    rec.p = ray._origin + (ray._direction * t);

    // Calculer la normale du triangle
    Vector3D normal(edge1._y * edge2._z - edge1._z * edge2._y,
                    edge1._z * edge2._x - edge1._x * edge2._z,
                    edge1._x * edge2._y - edge1._y * edge2._x);
    rec.normal = normal.normalized();

    return true;
}

void RayTracer::Triangle::init(const libconfig::Setting& setting)
{
    auto loadVertex = [](const libconfig::Setting& vertex, Point3D& point) {
        double x = 0.0;
        double y = 0.0;
        double z = 0.0;

        ConfigUtils::getAsDouble(vertex, "x", x);
        ConfigUtils::getAsDouble(vertex, "y", y);
        ConfigUtils::getAsDouble(vertex, "z", z);

        point = Point3D(x, y, z);
    };

    loadVertex(setting["v0"], _v0);
    loadVertex(setting["v1"], _v1);
    loadVertex(setting["v2"], _v2);

    if ((_v0._x == _v1._x && _v0._y == _v1._y && _v0._z == _v1._z) ||
        (_v0._x == _v2._x && _v0._y == _v2._y && _v0._z == _v2._z) ||
        (_v1._x == _v2._x && _v1._y == _v2._y && _v1._z == _v2._z)) {
        throw RayTracer::RayTracerException("Triangle: Vertices cannot be the same point.");
    }

    Vector3D edge1 = _v1 - _v0;
    Vector3D edge2 = _v2 - _v0;
    Vector3D normal(edge1._y * edge2._z - edge1._z * edge2._y,
                    edge1._z * edge2._x - edge1._x * edge2._z,
                    edge1._x * edge2._y - edge1._y * edge2._x);

    if (normal._x == 0.0 && normal._y == 0.0 && normal._z == 0.0)
        throw RayTracer::RayTracerException("Triangle: Vertices cannot be collinear.");

    if (setting.exists("color")) {
        const libconfig::Setting& c = setting["color"];
        double r = 255.0;
        double g = 255.0;
        double b = 255.0;
        ConfigUtils::getAsDouble(c, "r", r);
        ConfigUtils::getAsDouble(c, "g", g);
        ConfigUtils::getAsDouble(c, "b", b);
        color._x = static_cast<int>(r);
        color._y = static_cast<int>(g);
        color._z = static_cast<int>(b);
    }
}

extern "C" {
RayTracer::IPrimitive* entryPoint() { return new RayTracer::Triangle(); }
}
