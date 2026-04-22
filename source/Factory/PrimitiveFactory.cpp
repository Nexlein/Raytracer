/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** PrimitiveFactory
*/

#include "PrimitiveFactory.hpp"

#include "Plane.hpp"
#include "Sphere.hpp"

std::unique_ptr<RayTracer::IPrimitive> RayTracer::PrimitiveFactory::createSphere(
    const SphereData& sphere)
{
    auto createdSphere = std::make_unique<Sphere>(sphere.center, sphere.radius);
    createdSphere->color = sphere.color;

    return createdSphere;
}

std::unique_ptr<RayTracer::IPrimitive> RayTracer::PrimitiveFactory::createPlane(
    const PlaneData& plane)
{
    auto createdPlane = std::make_unique<Plane>(plane.axis, plane.position);
    createdPlane->color = plane.color;

    return createdPlane;
}
