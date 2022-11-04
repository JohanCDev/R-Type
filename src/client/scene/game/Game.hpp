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

class GameScene : public IScene {
  public:
    GameScene();

    void run(NetworkClient &client, sf::RenderWindow &window, SceneScreen &actual_screen) override;

    void init_game(sf::RenderWindow &window);

  private:
    Message<GameMessage> msg;
    World _world;
    bool _init;
};