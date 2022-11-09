/**
 * @file AllSystem.hpp
 * @author Cédric Corge (cedric.corge@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-10-17
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "../../client/client.hpp"
#include "../../server/game.hpp"
#include "../../server/server.hpp"
#include "../World.hpp"

enum class SceneScreen : uint32_t;

int drawable_system(World &world, sf::RenderWindow &window);
int controllable_system(World &world, sf::Event event);
int collide_system(World &world, NetworkServer &server);
int ia_system(World &world, NetworkServer &server);
int velocity_system(World &world);
int wave_system(World &world, NetworkServer &server, waves_t &waves);
int lobby_system(World &world, NetworkServer &server);
int clickable_system(World &world, Vector2i click_pos, SceneScreen &actual_screen, NetworkClient &client);
