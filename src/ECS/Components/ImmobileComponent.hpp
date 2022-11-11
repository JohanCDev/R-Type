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
    /**
     * @brief First value of the vector
     *
     * Will be used to know if the component move horizontally
     *
     */
    bool x;
    /**
     * @brief Second value of the vector
     *
     * Will be used to know if the component move vertically
     *
     */
    bool y;

    /**
     * @brief Construct a new Vector 2b object
     *
     * @param x_value Component moves horizontally ?
     * @param y_value Component moves vertically ?
     */
    Vector2b(bool x_value, bool y_value) : x(x_value), y(y_value)
    {
    }
};

/**
 * @brief Make the entity ignoring his velocity
 *
 */
struct ImmobileComponent {
    /**
     * @brief Vector containing the moving axis informations of component
     *
     */
    Vector2b axis;

    /**
     * @brief Construct a new Immobile Component object
     *
     * @param axis_vec
     */
    ImmobileComponent(Vector2b axis_vec) : axis(axis_vec){};
};
