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

class MenuScene : public IScene {
  public:
    MenuScene();
    SceneScreen run(sf::RenderWindow &window) override;

  private:
    World _world;

};