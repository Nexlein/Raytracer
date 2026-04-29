cmake_minimum_required(VERSION 3.5...4.0)
project(Raytracer LANGUAGES CXX)

# === GLOBAL CONFIGURATION ===
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)
find_package(PkgConfig QUIET)

# === INTERFACE TARGET (Common includes and flags) ===
add_library(raytracerGlobal INTERFACE)

target_compile_options(raytracerGlobal INTERFACE
    -Wall -Wextra -Werror -Wpedantic -Wold-style-cast -O3 -ffast-math
)

target_include_directories(raytracerGlobal INTERFACE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/include/Math
    ${PROJECT_SOURCE_DIR}/include/Core
    ${PROJECT_SOURCE_DIR}/include/Materials
    ${PROJECT_SOURCE_DIR}/include/Primitives
    ${PROJECT_SOURCE_DIR}/include/Light
    ${PROJECT_SOURCE_DIR}/include/Exceptions
    ${PROJECT_SOURCE_DIR}/include/Factory
    ${PROJECT_SOURCE_DIR}/include/Loader
)

# === DEPENDENCIES: LIBCONFIG++ ===
if(PKG_CONFIG_FOUND)
    pkg_check_modules(LIBCONFIGXX QUIET IMPORTED_TARGET libconfig++)
endif()

if(NOT LIBCONFIGXX_FOUND)
    message(STATUS "libconfig++ not found, fetching from GitHub...")

    set(CMAKE_POLICY_VERSION_MINIMUM "3.5" CACHE STRING "Minimum policy version" FORCE)

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

# Add libconfig++ to the global interface target
if(TARGET PkgConfig::LIBCONFIGXX)
    target_link_libraries(raytracerGlobal INTERFACE PkgConfig::LIBCONFIGXX)
else()
    # Fallback pour la version FetchContent
    target_link_libraries(raytracerGlobal INTERFACE config++)
    target_include_directories(raytracerGlobal INTERFACE ${libconfig_SOURCE_DIR}/lib)
endif()

# === PROJECT CORE ===
file(GLOB_RECURSE CORE_FILES CONFIGURE_DEPENDS "source/*.cpp")
list(FILTER CORE_FILES EXCLUDE REGEX "source/Primitives/.*\\.cpp$")
list(FILTER CORE_FILES EXCLUDE REGEX "source/Light/.*\\.cpp$")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

add_executable(raytracer ${CORE_FILES})
target_link_libraries(raytracer PRIVATE raytracerGlobal)
set_target_properties(raytracer PROPERTIES ENABLE_EXPORTS TRUE)

# === PLUGINS ===
set(PLUGIN_OUTPUT_DIR ${PROJECT_SOURCE_DIR}/plugins)

function(add_raytracer_plugin target_name source_file)
    add_library(${target_name} MODULE ${source_file})
    target_link_libraries(${target_name} PRIVATE raytracerGlobal)

    set_target_properties(${target_name} PROPERTIES
        PREFIX ""
        LIBRARY_OUTPUT_DIRECTORY ${PLUGIN_OUTPUT_DIR}
    )

    if(APPLE)
        set_target_properties(${target_name} PROPERTIES LINK_FLAGS "-undefined dynamic_lookup")
    endif()
endfunction()

add_raytracer_plugin(raytracer_sphere source/Primitives/Sphere.cpp)
add_raytracer_plugin(raytracer_plane source/Primitives/Plane.cpp)
add_raytracer_plugin(raytracer_triangle source/Primitives/Triangle.cpp)
add_raytracer_plugin(raytracer_cylinder source/Primitives/Cylinder.cpp)
add_raytracer_plugin(raytracer_obj source/Primitives/Obj.cpp)
add_raytracer_plugin(raytracer_ambientlight source/Light/AmbientLight.cpp)
add_raytracer_plugin(raytracer_directionallight source/Light/DirectionalLight.cpp)
add_raytracer_plugin(raytracer_lambertian source/Materials/Lambertian.cpp)
