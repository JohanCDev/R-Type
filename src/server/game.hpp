/**
 * @file game.hpp
 * @author Tanguy Bellicha (tanguy.bellicha@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-10-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "../Common/Message/Message.hpp"
#include "../Common/Message/MessageType.hpp"
#include "../ECS/World.hpp"
#include "server.hpp"

#define DEFAULT_PLAYER_POS_X 50
#define DEFAULT_PLAYER_POS_Y 200
#define DEFAULT_PLAYER_SPD   4
#define DEFAULT_PLAYER_HP    100
#define DEFAULT_PLAYER_SCALE 2.0
#define DEFAULT_LASER_SPD  4
#define DEFAULT_ENEMY_HP     100
#define DEFAULT_ENEMY_ATK    40
#define DEFAULT_ENEMY_SPD    6
#define DEFAULT_ENEMY_SCALE  1.0
#define DEFAULT_KEY_TOP      KeyboardInput::Z
#define DEFAULT_KEY_RGT      KeyboardInput::D
#define DEFAULT_KEY_BOT      KeyboardInput::S
#define DEFAULT_KEY_LFT      KeyboardInput::Q
#define DEFAULT_KEY_SHOOT    MouseInput::Left_click

/**
 * @brief Create a player in server's world and send the packet to the client
 *
 * @param world The server's world
 * @param msg The message received from the client
 * @param server The server
 */
void player_joined(World &world, ClientMessage msg, NetworkServer &server);

/**
 * @brief Destroy the player in server's world and send the packet to the client
 *
 * @param world The server's world
 * @param msg The message received from the client
 * @param server The server
 */
void player_left(World &world, ClientMessage msg, NetworkServer &server);

/**
 * @brief Move the player in the server's world and send the packet to the client
 *
 * @param world The server's world
 * @param msg The message received from the client
 * @param server The server
 */
void player_moved(World &world, ClientMessage msg, NetworkServer &server);

/**
 * @brief Create a shoot in the server's world and send the packet to the client
 *
 * @param world The server's world
 * @param msg The message received from the client
 * @param server The server
 */
void player_shot(World &world, ClientMessage msg, NetworkServer &server);

/**
 * @brief Create an enemy in the server's world and send the packet to the client
 *
 * @param world The server's world
 * @param server The server
 */
void create_enemy(World &world, NetworkServer &server);
