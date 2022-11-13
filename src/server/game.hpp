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

/**
 * @brief Default key to move to the top
 */
#define DEFAULT_KEY_TOP KeyboardInput::Z

/**
 * @brief Default key to move to the right
 */
#define DEFAULT_KEY_RGT KeyboardInput::D

/**
 * @brief Default key to move to the bottom
 */
#define DEFAULT_KEY_BOT KeyboardInput::S

/**
 * @brief Default key to move to the left
 */
#define DEFAULT_KEY_LFT KeyboardInput::Q

/**
 * @brief Default key to shoot
 */
#define DEFAULT_KEY_SHOOT MouseInput::Left_click

/**
 * @brief Default number of waves where boss spawn
 */
#define DEFAULT_WAVE_FREQUENCY_BOSS 5

/**
 * @brief Default increment multiplier difficulty between waves
 */
#define DEFAULT_WAVE_DIFFICULTY_MULTIPLIER 1.4

/**
 * @brief Default starting wave difficulty
 */
#define DEFAULT_WAVE_DIFFICULTY 10

/**
 * @brief Default time between each waves
 */
#define DEFAULT_WAVE_TIME_BETWEEN 5.0

/**
 * @brief Default time between each mini waves
 */
#define DEFAULT_MINI_WAVE_TIME_BETWEEN 0.8

/**
 * @brief Structure containing all the default values for the game
 *
 */
typedef struct myValues_s {
    /**
     * @brief Position of the object
     *
     */
    Vector2f pos;

    /**
     * @brief Health of the object
     *
     */
    int hp;

    /**
     * @brief Attack of the object
     *
     */
    int atk;

    /**
     * @brief Speed of the object
     *
     */
    int spd;

    /**
     * @brief Scale of the object
     *
     */
    float scale;
} myValues_t;

/**
 * @brief Default values for each GameObject (pos, hp, atk, spd, scale)
 */
static std::map<GameObject, myValues_t> defaultValues = {
    {GameObject::LASER, {{-1, -1}, 1, -1, 14, 1.0}},
    {GameObject::PLAYER, {{64, 540}, 100, 100, 12, 2.0}},
    {GameObject::SHIP_ARMORED, {{64, 540}, 150, 50, 12, 1.0}},
    {GameObject::SHIP_DAMAGE, {{64, 540}, 80, 120, 12, 1.0}},
    {GameObject::SHIP_ENGINEER, {{64, 540}, 100, 100, 12, 1.0}},
    {GameObject::SHIP_SNIPER, {{64, 540}, 150, 50, 12, 1.0}},
    {GameObject::BOSS_1, {{1920, 300}, 100, 40, 8, 2.0}},
    {GameObject::ENEMY_FOCUS, {{1920, -1}, 100, 40, 10, 1.0}},
    {GameObject::ENEMY_KAMIKAZE, {{1920, -1}, 100, 40, 20, 1.0}},
    {GameObject::ENEMY_SNIPER, {{1920, -1}, 100, 40, 10, 1.0}},
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
 * @brief start game
 *
 * @param world The server's world
 * @param msg Message to process
 * @param server The server
 */
void start_game(World &world, ClientMessage msg, NetworkServer &server);

/**
 * @brief Select a ship
 *
 * @param world The server's world
 * @param msg Message to process
 * @param server The server
 */
void select_ship(World &world, ClientMessage msg, NetworkServer &server);

/**
 * @brief Structure containing waves informations
 *
 * @param in_wave Boolean to know if the wave is in progress
 * @param nb_wave The number of the current wave
 * @param base_difficulty The difficulty of the wave
 * @param remaining_difficulty The remaining difficulty of the wave
 * @param clock The clock of the wave
 */
typedef struct wave_s {
    /**
     * @brief Boolean to know if the wave is in progress
     *
     */
    bool in_wave;

    /**
     * @brief The number of the current wave
     *
     */
    size_t nb_wave;

    /**
     * @brief The difficulty of the wave
     *
     */
    size_t base_difficulty;

    /**
     * @brief The remaining difficulty of the wave
     *
     */
    size_t remaining_difficulty;

    /**
     * @brief The clock of the wave
     *
     */
    sf::Clock clock;
} waves_t;
