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

#include "../Common/Message/Message.hpp"
#include "../Common/Message/MessageType.hpp"
#include "../ECS/World.hpp"

/**
 * @brief Create a player in the world
 *
 * @param world The world
 * @param srv_entity_id The server entity ID
 * @param pos The position of the entity
 * @param client Client network's information
 */
void new_player(World &world, size_t srv_entity_id, Vector2f pos, NetworkClient &client);

/**
 * @brief Create an armored player in the world
 *
 * @param world The world
 * @param srv_entity_id The server entity ID
 * @param pos The position of the entity
 * @param client Client network's information
 */
void new_armored_player(World &world, size_t srv_entity_id, Vector2f pos, NetworkClient &client);

/**
 * @brief Create a damage player in the world
 *
 * @param world The world
 * @param srv_entity_id The server entity ID
 * @param pos The position of the entity
 * @param client Client network's information
 */
void new_damage_player(World &world, size_t srv_entity_id, Vector2f pos, NetworkClient &client);

/**
 * @brief Create an engineer player in the world
 *
 * @param world The world
 * @param srv_entity_id The server entity ID
 * @param pos The position of the entity
 * @param client Client network's information
 */
void new_engineer_player(World &world, size_t srv_entity_id, Vector2f pos, NetworkClient &client);

/**
 * @brief Create a sniper player in the world
 *
 * @param world The world
 * @param srv_entity_id The server entity ID
 * @param pos The position of the entity
 * @param client Client network's information
 */
void new_sniper_player(World &world, size_t srv_entity_id, Vector2f pos, NetworkClient &client);

/**
 * @brief Create a enemy of type FOCUS in the world
 *
 * @param world The world
 * @param srv_entity_id The server entity ID
 * @param pos The position of the entity
 * @param client Client network's information
 */
void new_enemy_focus(World &world, size_t srv_entity_id, Vector2f pos, NetworkClient &client);

/**
 * @brief Create a enemy of type KAMIKAZE in the world
 *
 * @param world The world
 * @param srv_entity_id The server entity ID
 * @param pos The position of the entity
 * @param client Client network's information
 */
void new_enemy_kamikaze(World &world, size_t srv_entity_id, Vector2f pos, NetworkClient &client);

/**
 * @brief Create a enemy of type SNIPER in the world
 *
 * @param world The world
 * @param srv_entity_id The server entity ID
 * @param pos The position of the entity
 * @param client Client network's information
 */
void new_enemy_sniper(World &world, size_t srv_entity_id, Vector2f pos, NetworkClient &client);

/**
 * @brief Create a enemy of type ODD in the world
 *
 * @param world The world
 * @param srv_entity_id The server entity ID
 * @param pos The position of the entity
 * @param client Client network's information
 */
void new_enemy_odd(World &world, size_t srv_entity_id, Vector2f pos, NetworkClient &client);

/**
 * @brief Create a laser in the world
 *
 * @param world The world
 * @param srv_entity_id The server entity ID
 * @param pos The position of the entity
 * @param client Client network's information
 */
void new_laser(World &world, size_t srv_entity_id, Vector2f pos, NetworkClient &client);

/**
 * @brief Create a laser in the world for enemy team
 *
 * @param world The world
 * @param srv_entity_id The server entity ID
 * @param pos The position of the entity
 * @param client Client network's information
 */
void new_laser_enemy(World &world, size_t srv_entity_id, Vector2f pos, NetworkClient &client);

/**
 * @brief Create a enemy of type BOSS_A in the world
 *
 * @param world The world
 * @param srv_entity_id The server entity ID
 * @param pos The position of the entity
 * @param client Client network's information
 */
void new_boss1(World &world, size_t srv_entity_id, Vector2f pos, NetworkClient &client);

/**
 * @brief creation of attack bonus
 *
 * @param world The world
 * @param srv_entity_id The server entity ID
 * @param pos The position of the entity
 * @param client Client network's information
 */
void new_bonus_attack(World &world, size_t srv_entity_id, Vector2f pos, NetworkClient &client);

/**
 * @brief creation of attack speed bonus
 *
 * @param world The world
 * @param srv_entity_id The server entity ID
 * @param pos The position of the entity
 * @param client Client network's information
 */
void new_bonus_attack_speed(World &world, size_t srv_entity_id, Vector2f pos, NetworkClient &client);

/**
 * @brief creation of heal bonus
 *
 * @param world The world
 * @param srv_entity_id The server entity ID
 * @param pos The position of the entity
 * @param client Client network's information
 */
void new_bonus_heal(World &world, size_t srv_entity_id, Vector2f pos, NetworkClient &client);

/**
 * @brief creation of speed bonus
 *
 * @param world The world
 * @param srv_entity_id The server entity ID
 * @param pos The position of the entity
 * @param client Client network's information
 */
void new_bonus_speed(World &world, size_t srv_entity_id, Vector2f pos, NetworkClient &client);

/**
 * @brief creation of double laser bonus
 *
 * @param world The world
 * @param srv_entity_id The server entity ID
 * @param pos The position of the entity
 * @param client Client network's information
 */
void new_bonus_double(World &world, size_t srv_entity_id, Vector2f pos, NetworkClient &client);

/**
 * @brief Handle the movement message from the server
 *
 * @param world The world
 * @param client The client
 * @param event Event received
 */
void handle_movement(World &world, NetworkClient &client, sf::Event event);
