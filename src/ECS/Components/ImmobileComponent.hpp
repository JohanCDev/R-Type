/**
 * @file ImmobileComponent.hpp
 * @author Cédric CORGE (cedric.corge@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-09-27
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

/**
 * @brief Define a vector of boolean
 * 
 */
struct Vector2b {
    bool x;
    bool y;

    Vector2b(bool x_value, bool y_value) : x(x_value), y(y_value)
    {
    }
};

/**
 * @brief Make the entity ignoring his velocity
 * 
 */
struct ImmobileComponent {
    Vector2b axis;

    /**
     * @brief Construct a new Immobile Component object
     * 
     * @param axis_vec
     */
    ImmobileComponent(Vector2b axis_vec) : axis(axis_vec){};
};
