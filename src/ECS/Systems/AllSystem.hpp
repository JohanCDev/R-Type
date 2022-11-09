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

#include "../../server/game.hpp"
#include "../../server/server.hpp"
#include "../World.hpp"

/**
 * @brief Draw all drawables entities
 *
 * @param world The world
 * @return negative value if there is an error
 */
int drawable_system(World &world);

/**
 * @brief Update all controllable entities
 *
 * @param world The world
 * @param event Events received
 * @return negative value if there is an error
 */
int controllable_system(World &world, sf::Event event);

/**
 * @brief Check collision between entities if they have a collider
 *
 * @param world The world
 * @param server The server
 * @return negative value if there is an error
 */
int shooting_system(World &world, NetworkServer &server);

/**
 * @brief Call the AI function of each type of entities
 *
 * @param world The world
 * @param server The server
 * @return negative value if there is an error
 */
int ia_system(World &world, NetworkServer &server);

/**
 * @brief Move all movable entities
 *
 * @param world The world
 * @return negative value if there is an error
 */
int velocity_system(World &world);

/**
 * @brief Start a wave if needed
 *
 * @param world The world
 * @param server The server
 * @param waves Current wave
 * @return negative value if there is an error
 */
int wave_system(World &world, NetworkServer &server, waves_t &waves);
