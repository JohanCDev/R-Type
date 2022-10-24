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
#define DEFAULT_LASER_X_SPD  5
#define DEFAULT_LASER_Y_SPD  0
#define DEFAULT_ENEMY_HP     100
#define DEFAULT_ENEMY_ATK    40
#define DEFAULT_ENEMY_SPD    6
#define DEFAULT_ENEMY_SCALE  1.0
#define DEFAULT_KEY_TOP      KeyboardInput::Z
#define DEFAULT_KEY_RGT      KeyboardInput::D
#define DEFAULT_KEY_BOT      KeyboardInput::S
#define DEFAULT_KEY_LFT      KeyboardInput::Q
#define DEFAULT_KEY_SHOOT    MouseInput::Left_click

void process_informations(Message<GameMessage> msg, World &world);
void create_enemy(World &world, NetworkServer &server);