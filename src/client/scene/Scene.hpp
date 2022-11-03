/**
 * @file Scene.hpp
 * @author Cédric Corge (cedric.corge@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-10-31
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "../client.hpp"

enum class SceneScreen : uint32_t { MENU = 0, LOBBY, GAME };

class IScene {
  public:
    virtual ~IScene() = default;

    virtual void run(NetworkClient &client, sf::RenderWindow &window, SceneScreen &actual_screen) = 0;

  private:
};