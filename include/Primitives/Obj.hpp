/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Obj
*/

/// @file Obj.hpp
/// @brief Obj class definition for parsing .OBJ 3D models

#pragma once

#include <string>
#include <vector>

#include "IMaterial.hpp"
#include "IPrimitive.hpp"
#include "Point3D.hpp"

namespace RayTracer {
    /// @brief Lightweight triangle structure for internal OBJ use
    struct ObjTriangle {
        Math::Point3D<double> _v0;
        Math::Point3D<double> _v1;
        Math::Point3D<double> _v2;
        IMaterial* _material;

        [[nodiscard]] bool hits(const Ray& ray, HitRecord& hitRecord) const;
    };

    /// @brief Represents a 3D model loaded from an .OBJ file
    class Obj : public IPrimitive {
        public:
        Obj() = default;

        /// @brief Determines if a ray intersects the model by testing all its triangles
        /// @param ray The ray to test for intersection
        /// @param hitRecord The hit record to be filled with intersection details if the ray hits
        /// @return True if the ray intersects the model, false otherwise
        [[nodiscard]] bool hits(const Ray& ray, HitRecord& hitRecord) const override;

        /// @brief Initializes the model with settings from a configuration file (loads the .obj
        /// file)
        /// @param setting The configuration settings
        void init(const libconfig::Setting& setting) override;

        private:
        /// @brief Triangles that make up the model, parsed from the .OBJ file
        std::vector<ObjTriangle> _triangles;

        /// @brief Loads an .obj file and parses its vertices and faces into triangles
        /// @param filepath The path to the .obj file
        /// @param scale An optional scaling factor
        /// @param translation An optional translation vector
        void loadObjFile(const std::string& filepath, double scale,
                         const Math::Vector3D<double>& translation);

        /// @brief Parses a vertex from an input stream
        void parseVertex(std::istringstream& iss, std::vector<Math::Point3D<double>>& vertices,
                         double scale, const Math::Vector3D<double>& translation);

        /// @brief Parses a face from an input stream
        void parseFace(std::istringstream& iss, const std::vector<Math::Point3D<double>>& vertices);

        /// @brief Helper to parse vertex index with optional texture/normal coordinates
        int parseVertexIndex(const std::string& s) const;

        /// @brief Helper to get a vertex by index, handling negative indices
        Math::Point3D<double> getVertex(int idx,
                                        const std::vector<Math::Point3D<double>>& vertices) const;
    };
}  // namespace RayTracer
