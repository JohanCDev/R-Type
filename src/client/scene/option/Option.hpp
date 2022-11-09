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

class OptionScene : public IScene {
  public:
    OptionScene();
    void run(NetworkClient &client, sf::RenderWindow &window, SceneScreen &actual_screen) override;

    void init_option(sf::RenderWindow &window);

  private:
    World _world;
    bool _init;
};
