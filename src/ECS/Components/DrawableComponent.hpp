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

struct Vector4 {
    int x;
    int y;
    int x_size;
    int y_size;

    Vector4(int x_value, int y_value, int size_x, int size_y) : x(x_value), y(y_value), x_size(size_x), y_size(size_y)
    {
    }
};

struct DrawableComponent {
    std::string path;
    float x_scale;
    float y_scale;
    Vector4 rect;

    DrawableComponent(
        std::string texture_path, Vector4 vec = Vector4(0, 0, 0, 0), float xscale = 1.0, float yscale = 1.0)
        : path(texture_path), x_scale(xscale), y_scale(yscale), rect(vec)
    {
    }

    DrawableComponent() : rect(Vector4(0, 0, 0, 0)) {
    }

};
