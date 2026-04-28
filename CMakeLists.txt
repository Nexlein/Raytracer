cmake_minimum_required(VERSION 3.20...4.0)
project(Raytracer LANGUAGES CXX)

# === GLOBAL CONFIGURATION ===
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
find_package(PkgConfig QUIET)

# === INTERFACE TARGET (Common includes and flags) ===
# On crée une cible globale pour propager facilement nos options
add_library(raytracerGlobal INTERFACE)

target_compile_options(raytracerGlobal INTERFACE
    -Wall -Wextra -Werror -Wpedantic
    $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-std=c++26>
)

# On inclut automatiquement tous les sous-dossiers pertinents
target_include_directories(raytracerGlobal INTERFACE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/include/Math
    ${PROJECT_SOURCE_DIR}/include/Core
    ${PROJECT_SOURCE_DIR}/include/Primitives
    ${PROJECT_SOURCE_DIR}/include/Light
    ${PROJECT_SOURCE_DIR}/include/Exceptions
    ${PROJECT_SOURCE_DIR}/include/Factory
    ${PROJECT_SOURCE_DIR}/include/Loader
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

    set(CMAKE_WARN_DEPRECATED OFF CACHE BOOL "" FORCE)
    fetchcontent_makeavailable(libconfig)
    set(CMAKE_WARN_DEPRECATED ON CACHE BOOL "" FORCE)

    include(CheckSymbolExists)
    check_symbol_exists(uselocale "locale.h" HAVE_USELOCALE)
    check_symbol_exists(newlocale "locale.h" HAVE_NEWLOCALE)
    check_symbol_exists(freelocale "locale.h" HAVE_FREELOCALE)

    foreach(tgt config config++)
        if(TARGET ${tgt})
            if(HAVE_USELOCALE)
                target_compile_definitions(${tgt} PRIVATE HAVE_USELOCALE)
            endif()
            if(HAVE_NEWLOCALE)
                target_compile_definitions(${tgt} PRIVATE HAVE_NEWLOCALE)
            endif()
            if(HAVE_FREELOCALE)
                target_compile_definitions(${tgt} PRIVATE HAVE_FREELOCALE)
            endif()
        endif()
    endforeach()
else()
    message(STATUS "libconfig++ found via PkgConfig: ${LIBCONFIGXX_VERSION}")
endif()

# === PROJECT CORE ===
file(GLOB_RECURSE CORE_FILES CONFIGURE_DEPENDS "source/*.cpp")

list(FILTER CORE_FILES EXCLUDE REGEX "source/Primitives/.*\\.cpp$")
list(FILTER CORE_FILES EXCLUDE REGEX "source/Light/.*\\.cpp$")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
add_executable(raytracer ${CORE_FILES})
target_link_libraries(raytracer PRIVATE raytracerGlobal)
set_target_properties(raytracer PROPERTIES ENABLE_EXPORTS TRUE)

if(LIBCONFIGXX_FOUND)
    target_include_directories(raytracer PRIVATE ${LIBCONFIGXX_INCLUDE_DIRS})
    target_link_libraries(raytracer PRIVATE ${LIBCONFIGXX_LIBRARIES})
else()
    target_link_libraries(raytracer PRIVATE config++)
    target_include_directories(raytracer PRIVATE ${libconfig_SOURCE_DIR}/lib)
endif()

# === PLUGINS ===
set(PLUGIN_DIR "${PROJECT_SOURCE_DIR}/plugins")
file(MAKE_DIRECTORY ${PLUGIN_DIR})

# Sphere
add_library(raytracer_sphere SHARED source/Primitives/Sphere.cpp)
target_link_libraries(raytracer_sphere PRIVATE raytracerGlobal)
set_target_properties(raytracer_sphere PROPERTIES
    PREFIX ""
    LIBRARY_OUTPUT_DIRECTORY ${PLUGIN_DIR}
)

# Plane
add_library(raytracer_plane SHARED source/Primitives/Plane.cpp)
target_link_libraries(raytracer_plane PRIVATE raytracerGlobal)
set_target_properties(raytracer_plane PROPERTIES
    PREFIX ""
    LIBRARY_OUTPUT_DIRECTORY ${PLUGIN_DIR}
)

# AmbientLight
add_library(raytracer_ambientlight SHARED source/Light/AmbientLight.cpp)
target_link_libraries(raytracer_ambientlight PRIVATE raytracerGlobal)
set_target_properties(raytracer_ambientlight PROPERTIES
    PREFIX ""
    LIBRARY_OUTPUT_DIRECTORY ${PLUGIN_DIR}
)

# DirectionalLight
add_library(raytracer_directionallight SHARED source/Light/DirectionalLight.cpp)
target_link_libraries(raytracer_directionallight PRIVATE raytracerGlobal)
set_target_properties(raytracer_directionallight PROPERTIES
    PREFIX ""
    LIBRARY_OUTPUT_DIRECTORY ${PLUGIN_DIR}
)
add_compile_options(-Wold-style-cast)
