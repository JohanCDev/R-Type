/**
 * @file proto.hpp
 * @author Tanguy Bellicha (tanguy.bellicha@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-11-02
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "../ECS/World.hpp"
#include "../Common/Message/Message.hpp"
#include "../Common/Message/MessageType.hpp"

void new_player(World &world, size_t srv_entity_id, Vector2f pos);
void new_enemy_focus(World &world, size_t srv_entity_id, Vector2f pos);
void new_enemy_sniper(World &world, size_t srv_entity_id, Vector2f pos);
void new_enemy_odd(World &world, size_t srv_entity_id, Vector2f pos);
void new_laser(World &world, size_t srv_entity_id, Vector2f pos);
void new_boss1(World &world, size_t srv_entity_id, Vector2f pos);
