/**
 * @file Option.hpp
 * @author Cédric Corge (cedric.corge@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-11-03
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "../Scene.hpp"

class World;

/**
 * @brief Option scene of the game
 *
 */
class OptionScene : public IScene {
  public:
    /**
     * @brief Construct a new Option Scene object
     *
     */
    OptionScene();

    /**
     * @brief Run the option scene logic
     *
     * @param client Class containing client's network information
     * @param window Window to update
     * @param current_screen Current screen of the game
     * @param volume Volume of the sounds
     */
    void run(NetworkClient &client, sf::RenderWindow &window, SceneScreen &current_screen, float &volume) override;

    /**
     * @brief Initialize the option scene
     *
     * @param window Window to update
     */
    void init_option(sf::RenderWindow &window);

  private:
    /**
     * @brief World to act on
     *
     */
    World _world;

    /**
     * @brief Is the option screen initialized
     *
     */
    bool _init;
};
