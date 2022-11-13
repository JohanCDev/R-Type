/**
 * @file Lobby.hpp
 * @author Cédric Corge (cedric.corge@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-11-02
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "../Scene.hpp"

class World;

/**
 * @brief Lobby scene of the game
 *
 */
class LobbyScene : public IScene {
  public:
    /**
     * @brief Construct a new Lobby Scene object
     *
     */
    LobbyScene();

    /**
     * @brief Run the lobby scene logic
     *
     * @param client Class containing client's network information
     * @param window Window to update
     * @param current_screen Current screen of the game
     * @param volume Volume of the game
     */
    void run(NetworkClient &client, sf::RenderWindow &window, SceneScreen &current_screen, float &volume) override;

    /**
     * @brief Init the lobby scene
     *
     * @param window Window to update
     */
    void init_lobby(sf::RenderWindow &window);

    /**
     * @brief Update the number of players connected to lobby
     *
     * @param client Class containing client's network information
     */
    void update_player_number(NetworkClient &client);

  private:
    /**
     * @brief World to act on
     *
     */
    World _world;
    /**
     * @brief Is the client connected to the lobby
     *
     */
    bool _connected;
    /**
     * @brief Is the lobby initialized
     *
     */
    bool _init;
};
