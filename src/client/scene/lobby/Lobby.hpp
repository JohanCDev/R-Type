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

class LobbyScene : public IScene {
  public:
    LobbyScene();
    void run(NetworkClient &client, sf::RenderWindow &window, SceneScreen &actual_screen) override;

    void init_lobby(sf::RenderWindow &window);

    void update_player_number(NetworkClient &client);

  private:
    World _world;
    bool _connected;
    bool _init;
};
