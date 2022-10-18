/**
 * @file ResourcesManager.hpp
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

class ResourcesManager {
  public:
    ResourcesManager();
    ~ResourcesManager();

    void register_texture(const std::string path);
    sf::Texture get_texture(const std::string path);
    void register_font(const std::string path);
    sf::Font get_font(const std::string path);

  private:
    std::map<std::string, std::optional<sf::Texture>> _texture_map;
    std::map<std::string, std::optional<sf::Font>> _font_map;
};
