cmake_minimum_required(VERSION 3.20...4.0)
project(Raytracer LANGUAGES CXX)

# === GLOBAL CONFIGURATION ===
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
find_package(PkgConfig QUIET)

# === INTERFACE TARGET (Common includes and flags) ===
# On crée une cible globale pour propager facilement nos options
add_library(raytracerGlobal INTERFACE)

target_compile_options(raytracerGlobal INTERFACE
    -Wall -Wextra -Werror -Wpedantic
)

# On inclut automatiquement tous les sous-dossiers pertinents
target_include_directories(raytracerGlobal INTERFACE
    ${PROJECT_SOURCE_DIR}/RayTracer/include
    ${PROJECT_SOURCE_DIR}/RayTracer/include/Math
    ${PROJECT_SOURCE_DIR}/RayTracer/include/Core
    ${PROJECT_SOURCE_DIR}/RayTracer/include/Primitives
    ${PROJECT_SOURCE_DIR}/RayTracer/include/Lights
    ${PROJECT_SOURCE_DIR}/RayTracer/include/Exceptions
    ${PROJECT_SOURCE_DIR}/RayTracer/include/Factory
)

# === DEPENDENCIES: LIBCONFIG++ ===
if(PKG_CONFIG_FOUND)
    pkg_check_modules(LIBCONFIGXX QUIET libconfig++)
endif()

if(NOT LIBCONFIGXX_FOUND)
    message(STATUS "libconfig++ not found, fetching from GitHub...")

    set(BUILD_EXAMPLES OFF CACHE BOOL "Disable libconfig examples" FORCE)
    set(BUILD_TESTS OFF CACHE BOOL "Disable libconfig tests" FORCE)

    fetchcontent_declare(libconfig
        GIT_REPOSITORY https://github.com/hyperrealm/libconfig.git
        GIT_TAG v1.7.3
        GIT_SHALLOW TRUE
    )
    fetchcontent_makeavailable(libconfig)
else()
    message(STATUS "libconfig++ found via PkgConfig: ${LIBCONFIGXX_VERSION}")
endif()

# === PROJECT CORE ===
file(GLOB_RECURSE CORE_FILES CONFIGURE_DEPENDS "RayTracer/source/*.cpp")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
add_executable(raytracer ${CORE_FILES})

target_link_libraries(raytracer PRIVATE raytracerGlobal)

if(LIBCONFIGXX_FOUND)
    target_include_directories(raytracer PRIVATE ${LIBCONFIGXX_INCLUDE_DIRS})
    target_link_libraries(raytracer PRIVATE ${LIBCONFIGXX_LIBRARIES})
else()
    target_link_libraries(raytracer PRIVATE config++)
    target_include_directories(raytracer PRIVATE ${libconfig_SOURCE_DIR}/lib)
endif()
