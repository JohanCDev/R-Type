/**
 * @file DrawableComponent.hpp
 * @author Cédric Corge (cedric.corge@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-10-16
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <string>

/**
 * @brief Define the texture rect to draw
 *
 */
struct Vector4i {
    /**
     * @brief start of square in x
     *
     */
    int x;
    /**
     * @brief start of square in y
     *
     */
    int y;
    /**
     * @brief size of square in x
     *
     */
    int x_size;
    /**
     * @brief size of square in y
     *
     */
    int y_size;

    /**
     * @brief Construct a new Vector 4i object
     *
     * @param x_value start of square in x
     * @param y_value start of square in y
     * @param size_x size of square in x
     * @param size_y size of square in y
     */
    Vector4i(int x_value, int y_value, int size_x, int size_y) : x(x_value), y(y_value), x_size(size_x), y_size(size_y)
    {
    }
};

/**
 * @brief Define a vector of float
 *
 */
struct Vector2f {
    /**
     * @brief first value of the vector
     *
     */
    float x;
    /**
     * @brief second value of the vector
     *
     */
    float y;
};

/**
 * @brief Make the entity drawable
 *
 */
struct DrawableComponent {
    /**
     * @brief Path to the resource
     *
     */
    std::string path;

    /**
     * @brief Rectangle that will be shown at the draw
     *
     */
    Vector4i rect;

    /**
     * @brief Color of the component
     *
     */
    Vector4i color;

    /**
     * @brief Scale of the component
     *
     */
    Vector2f scale;

    /**
     * @brief Construct a new Drawable Component object
     *
     * @param texture_path Path to the resource
     * @param vec Rectangle to be shown
     * @param col Color of the rectangle
     * @param scale_vec Vector Scaling the entity
     */
    DrawableComponent(std::string texture_path, Vector4i vec = Vector4i(0, 0, 0, 0),
        Vector4i col = Vector4i(255, 255, 255, 255), Vector2f scale_vec = Vector2f{1.0, 1.0})
        : path(texture_path), rect(vec), color(col), scale(scale_vec)
    {
    }

    /**
     * @brief Construct a new Drawable Component object
     *
     * @param rect Rectangle to be shown
     * @param color Color of the component
     * @param scale Scale of the component
     *
     */
    DrawableComponent() : rect(Vector4i(0, 0, 0, 0)), color(Vector4i(255, 255, 255, 255)), scale(Vector2f{1.0, 1.0})
    {
    }
};
