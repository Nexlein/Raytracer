cmake_minimum_required(VERSION 3.20...4.0)
project(raytracer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

set(INC_DIR "RayTracer/include")
set(SRC_DIR "RayTracer/source")

include_directories(
    ${INC_DIR}
    ${INC_DIR}/Math
    ${INC_DIR}/Core
    ${INC_DIR}/Primitives
    ${INC_DIR}/Lights
    ${INC_DIR}/Exceptions
)

set(SOURCES
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/Math/Point3D.cpp
    ${SRC_DIR}/Math/Vector3D.cpp
    ${SRC_DIR}/Core/Ray.cpp
    ${SRC_DIR}/Core/Camera.cpp
    ${SRC_DIR}/Core/Rectangle3D.cpp
    ${SRC_DIR}/Primitives/Sphere.cpp
    ${SRC_DIR}/Exceptions/RayTracerException.cpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/..)
add_executable(raytracer ${SOURCES})
