/**
 * @file TextComponent.hpp
 * @author Cédric Corge (cedric.corge@epitech.eu)
 * @brief 
 * @version 0.1
 * @date 2022-11-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

struct TextComponent {

    std::string text;
    std::string font;
    int size;

    /**
     * @brief Construct a new Text Component object
     * 
     * @param text_string 
     * @param font_path 
     * @param text_size 
     */
    TextComponent(std::string text_string, std::string font_path, int text_size)
    : text(text_string), font(font_path), size(text_size) {}

};