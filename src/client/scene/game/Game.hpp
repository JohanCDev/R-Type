/**
 * @file Game.hpp
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

void handle_movement(World &world, NetworkClient &client, sf::Event event);

/**
 * @brief Game scene of the game
 *
 */
class GameScene : public IScene {
  public:
    /**
     * @brief Construct a new Game Scene object
     *
     */
    GameScene();

    /**
     * @brief Run the game scene logic
     *
     * @param client Class containing client's network information
     * @param window Window to update
     * @param current_screen Current screen of the game
     */
    void run(NetworkClient &client, sf::RenderWindow &window, SceneScreen &current_screen, float &volume) override;

    /**
     * @brief Initialize game screen
     *
     * @param window Window to update
     */
    void init_game(sf::RenderWindow &window);

    /**
     * @brief Update the position of parallax entities
     *
     */
    void update_parallax();

    /**
     * @brief Display the option screen
     *
     */
    void display_option(bool display);

  private:
    Message<GameMessage> msg;
    World _world;
    bool _init;
    bool _option;
};
