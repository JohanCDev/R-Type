/**
 * @file AssetsManager.hpp
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
#include <utility>
#include <optional>

class AssetsManager {

    public:

        AssetsManager() {
            sf::Texture texture;

            texture.loadFromFile("default.png");
            this->_texture_map.insert(std::make_pair("default", texture));
        }

        ~AssetsManager() {}

        void register_texture(const std::string path) {
            sf::Texture texture;

            if (!texture.loadFromFile(path)) {
                this->_texture_map.insert(std::make_pair(path, std::nullopt));
            } else {
                this->_texture_map.insert(std::make_pair(path, texture));
            }
        }

        sf::Texture get_texture(const std::string path) {
            if (this->_texture_map.find(path) == this->_texture_map.end()) {
                return (*this->_texture_map["default"]);
            } else if (!(this->_texture_map[path].has_value())) {
                return (*this->_texture_map["default"]);
            } else {
                return (*this->_texture_map[path]);
            }
        }

    private:
        std::map<std::string, std::optional<sf::Texture>> _texture_map;

};