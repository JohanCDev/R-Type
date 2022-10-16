/**
 * @file RessourcesManager.hpp
 * @author cédric CORGE (cedric.corge@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-09-27
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <SFML/Graphics.hpp>

#include <map>
#include <optional>
#include <utility>

class RessourcesManager {
  public:
    RessourcesManager()
    {
        sf::Texture texture;
        sf::Font font;

        texture.loadFromFile("default.png");
        this->_texture_map.insert(std::make_pair("default", texture));
        font.loadFromFile("default_font.ttf");
        this->_font_map.insert(std::make_pair("default_font", font));
    }

    ~RessourcesManager()
    {
    }

    void register_texture(const std::string path)
    {
        sf::Texture texture;

        if (!texture.loadFromFile(path)) {
            this->_texture_map.insert(std::make_pair(path, std::nullopt));
        } else {
            this->_texture_map.insert(std::make_pair(path, texture));
        }
    }

    sf::Texture get_texture(const std::string path)
    {
        if (this->_texture_map.find(path) == this->_texture_map.end()) {
            return (*this->_texture_map["default"]);
        } else if (!(this->_texture_map[path].has_value())) {
            return (*this->_texture_map["default"]);
        } else {
            return (*this->_texture_map[path]);
        }
    }

    void register_font(const std::string path)
    {
        sf::Font font;

        if (!font.loadFromFile(path)) {
            this->_font_map.insert(std::make_pair(path, std::nullopt));
        } else {
            this->_font_map.insert(std::make_pair(path, font));
        }
    }

    sf::Font get_font(const std::string path)
    {
        if (this->_font_map.find(path) == this->_font_map.end()) {
            return (*this->_font_map["default_font"]);
        } else if (!(this->_font_map[path].has_value())) {
            return (*this->_font_map["default_font"]);
        } else {
            return (*this->_font_map[path]);
        }
    }

  private:
    std::map<std::string, std::optional<sf::Texture>> _texture_map;
    std::map<std::string, std::optional<sf::Font>> _font_map;
};
