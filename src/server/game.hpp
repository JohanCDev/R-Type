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

#include <SFML/Graphics.hpp>
#include "../Common/Message/Message.hpp"
#include "../Common/Message/MessageType.hpp"
#include "../ECS/World.hpp"
#include "server.hpp"

#define DEFAULT_KEY_TOP                    KeyboardInput::Z
#define DEFAULT_KEY_RGT                    KeyboardInput::D
#define DEFAULT_KEY_BOT                    KeyboardInput::S
#define DEFAULT_KEY_LFT                    KeyboardInput::Q
#define DEFAULT_KEY_SHOOT                  MouseInput::Left_click
#define DEFAULT_WAVE_FREQUENCY_BOSS        2
#define DEFAULT_WAVE_DIFFICULTY_MULTIPLIER 1.4
#define DEFAULT_WAVE_DIFFICULTY            2
#define DEFAULT_WAVE_TIME_BETWEEN          5.0
#define DEFAULT_MINI_WAVE_TIME_BETWEEN     0.8

/**
 * @brief Structure containing all the default values for the game
 *
 * @param pos Position of the object
 * @param hp Health of the object
 * @param atk Attack of the object
 * @param spd Speed of the object
 * @param scale Scale of the object
 */
typedef struct values_s {
    Vector2f pos;
    int hp;
    int atk;
    int spd;
    float scale;
} values_t;

/**
 * @brief Default values for each GameObject (pos, hp, atk, spd, scale)
 */
static std::map<GameObject, values_t> defaultValues = {
    {GameObject::LASER, {{-1, -1}, 1, -1, 5, 1.0}},
    {GameObject::PLAYER, {{50, 200}, 100, 100, 6, 2.0}},
    {GameObject::BOSS_1, {{800, 300}, 100, 40, 4, 2.0}},
    {GameObject::ENEMY_FOCUS, {{800, -1}, 100, 40, 4, 1.0}},
    {GameObject::ENEMY_KAMIKAZE, {{800, -1}, 100, 40, 8, 1.0}},
    {GameObject::ENEMY_ODD, {{800, -1}, 100, 40, 4, 1.0}},
    {GameObject::ENEMY_SNIPER, {{800, -1}, 100, 40, 4, 1.0}},
};

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

/**
 * @brief
 *
 * @param in_wave Boolean to know if the wave is in progress
 * @param nb_wave The number of the current wave
 * @param base_difficulty The difficulty of the wave
 * @param remaining_difficulty The remaining difficulty of the wave
 * @param clock The clock of the wave
 */
typedef struct wave_s {
    bool in_wave;
    size_t nb_wave;
    size_t base_difficulty;
    size_t remaining_difficulty;
    sf::Clock clock;
} waves_t;
