/**
 * @file ResourcesManager.hpp
 * @author Cédric CORGE (cedric.corge@epitech.eu)
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

/**
 * @brief Storage of all resources of the game
 *
 */
class ResourcesManager {
  public:
    /**
     * @brief Construct a new Resources Manager object
     *
     */
    ResourcesManager();

    /**
     * @brief Destroy the Resources Manager object
     *
     */
    ~ResourcesManager();

    /**
     * @brief Register new texture into the manager
     *
     * @param path
     */
    void register_texture(const std::string path);

    /**
     * @brief Get the texture
     *
     * @param path
     * @return sf::Texture
     */
    sf::Texture get_texture(const std::string path);

    /**
     * @brief Register new font into the manager
     *
     * @param path
     */
    void register_font(const std::string path);

    /**
     * @brief Get the font
     *
     * @param path
     * @return sf::Font
     */
    sf::Font get_font(const std::string path);

  private:
    std::map<std::string, std::optional<sf::Texture>> _texture_map;
    std::map<std::string, std::optional<sf::Font>> _font_map;
};
