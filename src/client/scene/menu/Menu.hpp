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

class MenuScene : public IScene {
  public:
    MenuScene();
    void run(NetworkClient &client, sf::RenderWindow &window, SceneScreen &actual_screen) override;

    void init_menu(sf::RenderWindow &window);

  private:
    World _world;
    bool _init;

};