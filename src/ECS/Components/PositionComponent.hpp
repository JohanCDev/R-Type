/**
 * @file PositionComponent.hpp
 * @author Cédric Corge (cedric.corge@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-10-16
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

/**
 * @brief Define a vector of float
 * 
 */
struct Vector2i {
    int x;
    int y;

    Vector2i(int x_value, int y_value) : x(x_value), y(y_value)
    {
    }

    Vector2i() {
        x = 0;
        y = 0;
    }
};

/**
 * @brief Contains the entity position
 * 
 */
struct PositionComponent {
    Vector2i pos;

    /**
     * @brief Construct a new Position Component object
     * 
     * @param pos 
     */
    PositionComponent(Vector2i pos_vec) : pos(pos_vec) {};

};
