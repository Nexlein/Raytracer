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

RayTracer::Triangle::Triangle(
    const Point3D& v0, const Point3D& v1, const Point3D& v2) :
    _v0(v0), _v1(v1), _v2(v2)
{
    if (v0._x == v1._x && v0._y == v1._y && v0._z == v1._z)
        throw RayTracer::RayTracerException("Triangle: Vertices cannot be the same point.");
    if (v0._x == v2._x && v0._y == v2._y && v0._z == v2._z)
        throw RayTracer::RayTracerException("Triangle: Vertices cannot be the same point.");
    if (v1._x == v2._x && v1._y == v2._y && v1._z == v2._z)
        throw RayTracer::RayTracerException("Triangle: Vertices cannot be the same point.");
    
    Vector3D edge1 = v1 - v0;
    Vector3D edge2 = v2 - v0;
    Vector3D normal(
        edge1._y * edge2._z - edge1._z * edge2._y,
        edge1._z * edge2._x - edge1._x * edge2._z,
        edge1._x * edge2._y - edge1._y * edge2._x);

    if (normal._x == 0.0 && normal._y == 0.0 && normal._z == 0.0)
        throw RayTracer::RayTracerException("Triangle: Vertices cannot be collinear.");
}

bool RayTracer::Triangle::hits(const Ray& ray, HitRecord& rec) const
{
    const double epsilon = 1e-6;

    //Calcul des arêtes
    Vector3D edge1 = _v1 - _v0;
    Vector3D edge2 = _v2 - _v0;

    Vector3D pvec(
        ray._direction._y * edge2._z - ray._direction._z * edge2._y,
        ray._direction._z * edge2._x - ray._direction._x * edge2._z,
        ray._direction._x * edge2._y - ray._direction._y * edge2._x
    );

    double det = edge1.dot(pvec);

    // "det" proche de 0 = rayon parallèle au triangle
    if (std::abs(det) < epsilon) return false;

    double invDet = 1.0 / det;

    Vector3D tvec = ray._origin - _v0;
    double u = tvec.dot(pvec) * invDet;

    // "u" en dehors du triangle
    if (u < 0.0 || u > 1.0) return false;

    Vector3D qvec(
        tvec._y * edge1._z - tvec._z * edge1._y,
        tvec._z * edge1._x - tvec._x * edge1._z,
        tvec._x * edge1._y - tvec._y * edge1._x
    );
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
    Vector3D normal(
        edge1._y * edge2._z - edge1._z * edge2._y,
        edge1._z * edge2._x - edge1._x * edge2._z,
        edge1._x * edge2._y - edge1._y * edge2._x
    );
    rec.normal = normal.normalized();

    return true;
}

void RayTracer::Triangle::init(const libconfig::Setting& setting)
{
    if (setting.exists("v0")) {
        const libconfig::Setting& v0 = setting["v0"];
        double x = 0.0;
        double y = 0.0;
        double z = 0.0;
        ConfigUtils::getAsDouble(v0, "x", x);
        ConfigUtils::getAsDouble(v0, "y", y);
        ConfigUtils::getAsDouble(v0, "z", z);
        _v0 = Point3D(x, y, z);
    }

    if (setting.exists("v1")) {
        const libconfig::Setting& v1 = setting["v1"];
        double x = 0.0;
        double y = 0.0;
        double z = 0.0;
        ConfigUtils::getAsDouble(v1, "x", x);
        ConfigUtils::getAsDouble(v1, "y", y);
        ConfigUtils::getAsDouble(v1, "z", z);
        _v1 = Point3D(x, y, z);
    }

    if (setting.exists("v2")) {
        const libconfig::Setting& v2 = setting["v2"];
        double x = 0.0;
        double y = 0.0;
        double z = 0.0;
        ConfigUtils::getAsDouble(v2, "x", x);
        ConfigUtils::getAsDouble(v2, "y", y);
        ConfigUtils::getAsDouble(v2, "z", z);
        _v2 = Point3D(x, y, z);
    }

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
