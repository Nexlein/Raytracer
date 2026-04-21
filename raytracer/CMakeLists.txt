cmake_minimum_required(VERSION 3.20...4.0)
project(raytracer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

include_directories(include)

set(SOURCES
    source/main.cpp
    source/Math/Point3D.cpp
    source/Math/Vector3D.cpp
    source/Core/Ray.cpp
    source/Core/Camera.cpp
    source/Core/Rectangle3D.cpp
    source/Primitives/Sphere.cpp
    source/RayTracerException.cpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/..)
add_executable(raytracer ${SOURCES})
