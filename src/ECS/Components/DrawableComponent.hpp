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
 * @param x start of square in x
 * @param y start of square in y
 * @param x_size size of square in x
 * @param y_size size of square in y
 */
struct Vector4i {
    int x;
    int y;
    int x_size;
    int y_size;

    Vector4i(int x_value, int y_value, int size_x, int size_y) : x(x_value), y(y_value), x_size(size_x), y_size(size_y)
    {
    }
};

/**
 * @brief Define a vector of float
 *
 */
struct Vector2f {
    float x;
    float y;
};

/**
 * @brief Make the entity drawable
 *
 */
struct DrawableComponent {
    std::string path;
    Vector4i rect;
    Vector2f scale;

    /**
     * @brief Construct a new Drawable Component object
     *
     * @param texture_path
     * @param vec
     * @param xscale
     * @param yscale
     */
    DrawableComponent(
        std::string texture_path, Vector4i vec = Vector4i(0, 0, 0, 0), Vector2f scale_vec = Vector2f{1.0, 1.0})
        : path(texture_path), rect(vec), scale(scale_vec)
    {
    }

    DrawableComponent() : rect(Vector4i(0, 0, 0, 0)), scale(Vector2f{1.0, 1.0})
    {
    }
};
