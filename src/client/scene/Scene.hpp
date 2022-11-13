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
#include "callback/AllCallback.hpp"

/**
 * @brief All scenes represented as an enum going from 0 to 4
 *
 */
enum class SceneScreen : uint32_t { MENU = 0, LOBBY, GAME, OPTION, NONE };

/**
 * @brief Interface for all scenes
 *
 */
class IScene {
  public:
    /**
     * @brief Destroy the IScene object
     *
     */
    virtual ~IScene() = default;

    /**
     * @brief Run the screen logic
     *
     * @param client Class containing client's network information
     * @param window Window to update
     * @param current_screen Current screen of the game
     * @param volume Volume of the game
     */
    virtual void run(NetworkClient &client, sf::RenderWindow &window, SceneScreen &current_screen, float &volume) = 0;

  private:
};
