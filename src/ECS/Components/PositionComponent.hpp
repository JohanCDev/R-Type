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
    /**
     * @brief First value of the vector
     *
     */
    int x;
    /**
     * @brief Second value of the vector
     *
     */
    int y;

    /**
     * @brief Add two vectors
     *
     * @param other vector to add
     * @return Vector2i& result of the addition
     */
    Vector2i &operator+=(const Vector2i &other)
    {
        x += other.x;
        y += other.y;
        return (*this);
    }

    /**
     * @brief Check if two vectors are equal
     *
     * @param other vector to compare
     * @return true if equal
     * @return false if not equal
     */
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
    /**
     * @brief Position as a Vector2f
     *
     */
    Vector2f pos;

    /**
     * @brief Construct a new Position Component object
     *
     * @param pos_vec Position of the component
     */
    PositionComponent(Vector2f pos_vec) : pos(pos_vec){};
};
