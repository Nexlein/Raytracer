/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Sphere
*/

/// @file Sphere.cpp
/// @brief Implementation of the Sphere class.

#include "Torus.hpp"

#include "ConfigUtils.hpp"
#include "RayTracerException.hpp"

int RayTracer::Torus::solveQuadratic(const QuadraticCoeffs& coeffs, double roots[2]) const
{
    double a = coeffs.a;
    double b = coeffs.b;
    double c = coeffs.c;
    if (std::abs(a) < 1e-9) {
        if (std::abs(b) < 1e-9) return 0;
        roots[0] = -c / b;
        return 1;
    }
    double disc = b * b - 4 * a * c;
    if (disc < 0) return 0;
    if (std::abs(disc) < 1e-12) {
        roots[0] = -b / (2 * a);
        return 1;
    }
    double sqrt_disc = std::sqrt(disc);
    roots[0] = (-b - sqrt_disc) / (2 * a);
    roots[1] = (-b + sqrt_disc) / (2 * a);
    return 2;
}

int RayTracer::Torus::solveCubic(const CubicCoeffs& coeffs, double roots[3]) const
{
    double a = coeffs.a;
    double b = coeffs.b;
    double c = coeffs.c;
    double d = coeffs.d;
    if (std::abs(a) < 1e-9) return solveQuadratic({b, c, d}, roots);

    double A = b / a;
    double B = c / a;
    double C = d / a;
    double Q = (3.0 * B - A * A) / 9.0;
    double R = (9.0 * A * B - 27.0 * C - 2.0 * A * A * A) / 54.0;
    double D = Q * Q * Q + R * R;

    if (D > 0) {
        double S = std::cbrt(R + std::sqrt(D));
        double T = std::cbrt(R - std::sqrt(D));
        roots[0] = -A / 3.0 + (S + T);
        return 1;
    } else if (std::abs(D) < 1e-12) {
        double S = std::cbrt(R);
        roots[0] = -A / 3.0 + 2.0 * S;
        roots[1] = -A / 3.0 - S;
        return 2;
    } else {
        double arg = R / std::sqrt(-Q * Q * Q);
        double theta = std::acos(std::max(-1.0, std::min(1.0, arg)));
        double sqrtQ = 2.0 * std::sqrt(-Q);
        roots[0] = sqrtQ * std::cos(theta / 3.0) - A / 3.0;
        roots[1] = sqrtQ * std::cos((theta + 2.0 * M_PI) / 3.0) - A / 3.0;
        roots[2] = sqrtQ * std::cos((theta + 4.0 * M_PI) / 3.0) - A / 3.0;
        return 3;
    }
}

int RayTracer::Torus::solveQuartic(const QuarticCoeffs& coeffs, double roots[4]) const
{
    if (std::abs(coeffs.a) < 1e-9)
        return solveCubic({coeffs.b, coeffs.c, coeffs.d, coeffs.e}, roots);

    double A = coeffs.b / coeffs.a;
    double B = coeffs.c / coeffs.a;
    double C = coeffs.d / coeffs.a;
    double D = coeffs.e / coeffs.a;

    double cub_roots[3];
    solveCubic({1.0, -B, (A * C - 4.0 * D), (4.0 * B * D - A * A * D - C * C)}, cub_roots);
    double y = cub_roots[0];

    double p_sq = A * A / 4.0 - B + y;
    if (p_sq < 0) {
        if (p_sq > -1e-7)
            p_sq = 0;
        else
            return 0;
    }

    double p = std::sqrt(p_sq);
    double q;
    if (p > 1e-9) {
        q = (A * y / 2.0 - C) / (2.0 * p);
    } else {
        double q_sq = y * y / 4.0 - D;
        if (q_sq < 0) {
            if (q_sq > -1e-7)
                q_sq = 0;
            else
                return 0;
        }
        q = std::sqrt(q_sq);
    }

    int count = solveQuadratic({1.0, A / 2.0 + p, y / 2.0 + q}, roots);
    count += solveQuadratic({1.0, A / 2.0 - p, y / 2.0 - q}, roots + count);

    return count;
}

bool RayTracer::Torus::hits(const Ray& ray, HitRecord& rec) const
{
    rec.primitive = this;
    rec.material = _material.get();

    Vector3D orig = ray._origin - _position;
    Vector3D dir = ray._direction;

    // Rotation inverse
    orig.rotateX(-_rotation._x);
    orig.rotateY(-_rotation._y);
    orig.rotateZ(-_rotation._z);
    dir.rotateX(-_rotation._x);
    dir.rotateY(-_rotation._y);
    dir.rotateZ(-_rotation._z);

    double ox = orig._x, oy = orig._y, oz = orig._z;
    double dx = dir._x, dy = dir._y, dz = dir._z;

    double R = _outer_radius, r = _inner_radius;

    double sum_d_sq = dx * dx + dy * dy + dz * dz;
    double od = ox * dx + oy * dy + oz * dz;
    double K = ox * ox + oy * oy + oz * oz - R * R - r * r;

    QuarticCoeffs coeffs = {sum_d_sq * sum_d_sq, 4.0 * od * sum_d_sq,
                            2.0 * sum_d_sq * K + 4.0 * od * od + 4.0 * R * R * dy * dy,
                            4.0 * od * K + 8.0 * R * R * oy * dy,
                            K * K - 4.0 * R * R * (r * r - oy * oy)};

    double roots[4];
    int num_roots = solveQuartic(coeffs, roots);

    if (num_roots == 0) return false;

    double closest = std::numeric_limits<double>::infinity();
    for (int i = 0; i < num_roots; i++) {
        if (roots[i] > 0.001 && roots[i] < closest) closest = roots[i];
    }

    if (closest == std::numeric_limits<double>::infinity()) return false;

    rec.distance = closest;
    rec.p = ray._origin + ray._direction * closest;

    Vector3D p = rec.p - _position;
    p.rotateX(-_rotation._x);
    p.rotateY(-_rotation._y);
    p.rotateZ(-_rotation._z);

    double xz_dist = std::sqrt(p._x * p._x + p._z * p._z);
    if (xz_dist < 1e-6) return false;

    rec.normal =
        Vector3D(p._x * (1.0 - R / xz_dist), p._y, p._z * (1.0 - R / xz_dist)).normalized();

    // Rotation normale dans le sens normal
    rec.normal.rotateX(_rotation._x);
    rec.normal.rotateY(_rotation._y);
    rec.normal.rotateZ(_rotation._z);
    rec.normal = rec.normal.normalized();

    return true;
}

void RayTracer::Torus::init(const libconfig::Setting& setting)
{
    ConfigUtils::parsePoint3D(setting, "position", _position, true);

    ConfigUtils::parseVector3D(setting, "rotation", _rotation, false);

    Math::Vector3D<double> translation;
    ConfigUtils::parseVector3D(setting, "translation", translation, false);
    _position = _position + translation;

    if (!ConfigUtils::getAsDouble(setting, "outer_radius", _outer_radius))
        throw RayTracer::RayTracerException("Torus: Missing required parameter 'outer_radius'.");

    if (!ConfigUtils::getAsDouble(setting, "inner_radius", _inner_radius))
        throw RayTracer::RayTracerException("Torus: Missing required parameter 'outer_radius'.");

    if (setting.exists("material")) {
        std::string name = setting["material"];
        _materialName = name;
    }
}

extern "C" {
RayTracer::IPrimitive* entryPoint() { return new RayTracer::Torus(); }
}
