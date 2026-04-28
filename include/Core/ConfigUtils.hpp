/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** ConfigUtils
*/

/// @file ConfigUtils.hpp
/// @brief Configuration utilities

#pragma once

#include <libconfig.h++>

namespace RayTracer {
    namespace ConfigUtils {
        /// @brief Helper function to extract a double value from a libconfig setting
        /// @param setting The libconfig setting to extract the value from
        /// @param key The key of the value to extract
        /// @param value The variable to store the extracted value
        /// @return True if the value was successfully extracted, false otherwise
        inline bool getAsDouble(const libconfig::Setting& setting, const std::string& key, double& value)
        {
            int intValue = 0;
            if (setting.lookupValue(key.c_str(), intValue)) {
                value = static_cast<double>(intValue);
                return true;
            }

            float floatValue = 0.0f;
            if (setting.lookupValue(key.c_str(), floatValue)) {
                value = static_cast<double>(floatValue);
                return true;
            }

            return setting.lookupValue(key.c_str(), value);
        }
    }  // namespace ConfigUtils
}  // namespace RayTracer
