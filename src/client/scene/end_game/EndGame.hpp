/**
 * @file EndGame.hpp
 * @author Cédric Corge (cedric.corge@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-11-13
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "../Scene.hpp"

class World;

/**
 * @brief end game scene of the game
 *
 */
class EndGameScene : public IScene {
  public:
    /**
     * @brief Construct a new end game Scene object
     *
     */
    EndGameScene();

    /**
     * @brief Run the end game scene logic
     *
     * @param client Class containing client's network information
     * @param window Window to update
     * @param current_screen Current screen of the game
     */
    void run(NetworkClient &client, sf::RenderWindow &window, SceneScreen &current_screen, float &volume) override;

    /**
     * @brief Initialize the end game scene
     *
     * @param window Window to update
     */
    void init_end_game(sf::RenderWindow &window);

  private:
    /**
     * @brief World to act on
     *
     */
    World _world;

    /**
     * @brief Is the end game screen initialized
     *
     */
    bool _init;
};
