/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Obj
*/

/// @file Obj.cpp
/// @brief Implementation of the Obj class.

#include "Obj.hpp"

#include <cmath>
#include <fstream>
#include <limits>
#include <sstream>

#include "ConfigUtils.hpp"
#include "RayTracerException.hpp"

bool RayTracer::ObjTriangle::hits(const Ray& ray, HitRecord& rec) const
{
    const double epsilon = 1e-6;

    // 1. Define the triangle's edges
    Math::Vector3D<double> edge1 = _v1 - _v0;
    Math::Vector3D<double> edge2 = _v2 - _v0;

    // 2. Calculate determinant to check if ray is parallel to the triangle
    Math::Vector3D<double> pvec(ray._direction._y * edge2._z - ray._direction._z * edge2._y,
                                ray._direction._z * edge2._x - ray._direction._x * edge2._z,
                                ray._direction._x * edge2._y - ray._direction._y * edge2._x);

    double det = edge1.dot(pvec);
    // If determinant is close to 0, ray is parallel to the triangle
    if (std::abs(det) < epsilon) return false;

    double invDet = 1.0 / det;

    // 3. Calculate U parameter (barycentric coordinate) and test bounds
    Math::Vector3D<double> tvec = ray._origin - _v0;
    double u = tvec.dot(pvec) * invDet;

    // If U is outside [0, 1], the hit is outside the triangle
    if (u < 0.0 || u > 1.0) return false;

    // 4. Calculate V parameter and test bounds
    Math::Vector3D<double> qvec(tvec._y * edge1._z - tvec._z * edge1._y,
                                tvec._z * edge1._x - tvec._x * edge1._z,
                                tvec._x * edge1._y - tvec._y * edge1._x);
    double v = ray._direction.dot(qvec) * invDet;

    // If V is outside or U+V > 1, the hit is outside the triangle
    if (v < 0.0 || u + v > 1.0) return false;

    // 5. Calculate T (distance to intersection point)
    double t = edge2.dot(qvec) * invDet;

    // If T is negative, the triangle is behind the camera
    if (t <= epsilon) return false;

    // 6. Valid hit -> Save the hit info
    rec.distance = t;
    rec.p = ray._origin + (ray._direction * t);

    // Calculate the face normal using cross product of edges
    Math::Vector3D<double> normal(edge1._y * edge2._z - edge1._z * edge2._y,
                                  edge1._z * edge2._x - edge1._x * edge2._z,
                                  edge1._x * edge2._y - edge1._y * edge2._x);
    rec.normal = normal.normalized();

    return true;
}

bool RayTracer::Obj::hits(const Ray& ray, HitRecord& hitRecord) const
{
    bool hitAnything = false;
    double closestSoFar = std::numeric_limits<double>::infinity();
    HitRecord tempRec;

    for (const auto& triangle : _triangles) {
        if (triangle.hits(ray, tempRec)) {
            if (tempRec.distance < closestSoFar) {
                closestSoFar = tempRec.distance;
                hitRecord = tempRec;
                hitAnything = true;
            }
        }
    }

    if (hitAnything) hitRecord.normal = hitRecord.normal.normalized();

    hitRecord.material = _material.get();
    return hitAnything;
}

int RayTracer::Obj::parseVertexIndex(const std::string& s) const
{
    size_t pos = s.find('/');
    if (pos != std::string::npos) return std::stoi(s.substr(0, pos));
    return std::stoi(s);
}

Math::Point3D<double> RayTracer::Obj::getVertex(
    int idx, const std::vector<Math::Point3D<double>>& vertices) const
{
    if (idx > 0) return vertices[idx - 1];
    if (idx < 0) return vertices[vertices.size() + idx];
    throw RayTracerException("Obj: Invalid vertex index 0");
}

void RayTracer::Obj::parseVertex(std::istringstream& iss,
                                 std::vector<Math::Point3D<double>>& vertices, double scale,
                                 const Math::Vector3D<double>& position)
{
    double x, y, z;
    iss >> x >> y >> z;
    x = x * scale + position._x;
    y = y * scale + position._y;
    z = z * scale + position._z;
    vertices.emplace_back(x, y, z);
}

void RayTracer::Obj::parseFace(std::istringstream& iss,
                               const std::vector<Math::Point3D<double>>& vertices)
{
    std::string v1_str, v2_str, v3_str;
    if (!(iss >> v1_str >> v2_str >> v3_str)) return;

    int i1 = parseVertexIndex(v1_str);
    int i2 = parseVertexIndex(v2_str);
    int i3 = parseVertexIndex(v3_str);

    try {
        ObjTriangle t;
        t._v0 = getVertex(i1, vertices);
        t._v1 = getVertex(i2, vertices);
        t._v2 = getVertex(i3, vertices);
        t._material = _material.get();
        _triangles.push_back(t);

        // Handle quads
        std::string v4_str;
        if (iss >> v4_str) {
            int i4 = parseVertexIndex(v4_str);
            ObjTriangle t2;
            t2._v0 = getVertex(i1, vertices);
            t2._v1 = getVertex(i3, vertices);
            t2._v2 = getVertex(i4, vertices);
            t2._material = _material.get();
            _triangles.push_back(t2);
        }
    } catch (const RayTracerException&) {
        // Ignore degenerate triangles
    }
}

void RayTracer::Obj::loadObjFile(const std::string& filepath, double scale,
                                 const Math::Vector3D<double>& position)
{
    std::ifstream file(filepath);
    if (!file.is_open()) throw RayTracerException("Obj: Could not open file " + filepath);

    std::vector<Math::Point3D<double>> vertices;
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

        std::istringstream iss(line);
        std::string type;
        iss >> type;

        if (type == "v")
            parseVertex(iss, vertices, scale, position);
        else if (type == "f")
            parseFace(iss, vertices);
    }
}

void RayTracer::Obj::init(const libconfig::Setting& setting)
{
    if (setting.exists("material")) {
        std::string name = setting["material"];
        _materialName = name;
    }

    double scale = 1.0;
    if (setting.exists("scale")) ConfigUtils::getAsDouble(setting, "scale", scale);

    Math::Vector3D<double> position(0.0, 0.0, 0.0);
    if (setting.exists("position")) {
        const libconfig::Setting& pos = setting["position"];
        double tx = 0.0, ty = 0.0, tz = 0.0;
        ConfigUtils::getAsDouble(pos, "x", tx);
        ConfigUtils::getAsDouble(pos, "y", ty);
        ConfigUtils::getAsDouble(pos, "z", tz);
        position = {tx, ty, tz};
    }

    if (setting.exists("file")) {
        std::string filepath;
        setting.lookupValue("file", filepath);
        loadObjFile(filepath, scale, position);
    } else
        throw RayTracerException("Obj: Missing 'file' parameter.");
}

extern "C" {
RayTracer::IPrimitive* entryPoint() { return new RayTracer::Obj(); }
}
