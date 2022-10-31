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
#include "../../client.hpp"

void handle_movement(World &world, NetworkClient &client, sf::Event event);

class GameScene : public IScene {
  public:
    GameScene();

    SceneScreen run(sf::RenderWindow &window) override;

  private:
    Message<GameMessage> msg;
    NetworkClient _client;
    World _world;
    bool _connected;
};