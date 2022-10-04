/**
 * @file ShapeComponent.hpp
 * @author Cédric Corge (cedric.corge@epitech.eu)
 * @brief 
 * @version 0.1
 * @date 2022-10-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include <string>

enum shape_type {
    RECTANGLE,
    TRIANGLE,
    CIRCLE,
    TEXT
};

struct ShapeComponent {

    float x_scale;
	float y_scale;
    shape_type type;
    int radius;
    int side;
    int length;
    int width;
    std::string font;
    std::string text;
    int font_size;

    ShapeComponent(enum shape_type shape, int length) {
        if (shape == shape_type::CIRCLE) {
            type = shape;
            radius = length;
        } else {
            type = shape;
            side = length;
        }
    }

    ShapeComponent(enum shape_type type_shape, int length_value, int width_value)
    : type(type_shape), length(length_value), width(width_value) {}

    ShapeComponent(enum shape_type type_shape, std::string text_string, std::string font_path, int char_size)
    : type(type_shape), text(text_string), font(font_path), font_size(char_size) {}

};