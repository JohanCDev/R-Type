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
 * @brief Define a vector of int
 *
 */
struct Vector2i {
    int x;
    int y;

    Vector2i &operator+=(const Vector2i &other)
    {
        x += other.x;
        y += other.y;
        return (*this);
    }

    bool operator!=(const Vector2i &other)
    {
        return (x != other.x || y != other.y);
    }
};

/**
 * @brief Contains the entity position
 *
 */
struct PositionComponent {
    Vector2f pos;

    /**
     * @brief Construct a new Position Component object
     *
     * @param pos
     */
    PositionComponent(Vector2f pos_vec) : pos(pos_vec){};
};
