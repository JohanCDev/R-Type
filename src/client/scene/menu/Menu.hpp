/**
 * @file Menu.hpp
 * @author Cédric Corge (cedric.corge@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-10-31
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "../Scene.hpp"

class World;

/**
 * @brief Menu scene of the game
 *
 */
class MenuScene : public IScene {
  public:
    /**
     * @brief Construct a new Menu Scene object
     *
     */
    MenuScene();

    /**
     * @brief Run the menu scene logic
     *
     * @param client Class containing client's network information
     * @param window Window to update
     * @param current_screen Current screen of the game
     * @param volume Volume of the game
     */
    void run(NetworkClient &client, sf::RenderWindow &window, SceneScreen &current_screen, float &volume) override;

    /**
     * @brief Init the menu scene
     *
     * @param window Window to update
     */
    void init_menu(sf::RenderWindow &window);

  private:
    /**
     * @brief World to act on
     *
     */
    World _world;

    /**
     * @brief Is the menu initialized
     *
     */
    bool _init;
};
