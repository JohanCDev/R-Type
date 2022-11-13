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
#include <chrono>
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
 * @brief Default time of dispawn bonus
 *
 */
#define BOOST_DISPAWN 8.0

/**
 * @brief Default time of bonus timer
 *
 */
#define BOOST_TIMER 4.0

/**
 * @brief Structure containing all the default values for the game
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
    {GameObject::LASER_ENEMY, {{-1, -1}, 1, -1, -14, -1.0}},
    {GameObject::PLAYER, {{64, 540}, 100, 100, 12, 2.0}},
    {GameObject::SHIP_ARMORED, {{64, 540}, 200, 50, 12, 1.0}},
    {GameObject::SHIP_DAMAGE, {{64, 540}, 80, 120, 14, 1.0}},
    {GameObject::SHIP_ENGINEER, {{64, 540}, 100, 100, 12, 1.0}},
    {GameObject::SHIP_SNIPER, {{64, 540}, 100, 200, 10, 1.0}},
    {GameObject::BOSS_1, {{1920, 300}, 2000, 40, 8, 2.0}},
    {GameObject::ENEMY_FOCUS, {{1920, -1}, 100, 40, 10, 1.0}},
    {GameObject::ENEMY_KAMIKAZE, {{1920, -1}, 100, 40, 20, 1.0}},
    {GameObject::ENEMY_SNIPER, {{1920, -1}, 100, 40, 10, 0.75}},
};

int check_collision(ResourcesManager &manager, sf::Sprite sprite, std::optional<PositionComponent> &position,
    std::optional<DrawableComponent> &drawable);

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
 * @brief Creation of bonus
 *
 * @param world The server's world
 * @param server server informations
 * @param pos bonus position
 */
void bonus_creation(World &world, NetworkServer &server, Vector2f pos);

/**
 * @brief Start the game
 *
 * @param world The server's world
 * @param msg Message to process
 * @param server server informations
 */
void start_game(World &world, ClientMessage msg, NetworkServer &server);

/**
 * @brief Select the ship
 *
 * @param world The server's world
 * @param msg Message to process
 * @param server server informations
 */
void select_ship(World &world, ClientMessage msg, NetworkServer &server);

/**
 * @brief Structure containing wave information
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

/**
 * @brief Struct containing bonus statistics
 */
typedef struct stat_bonus_s {
    /**
     * @brief Speed bonus
     *
     */
    int speed;
    /**
     * @brief Strength bonus
     *
     */
    int strengh;
    /**
     * @brief Fire rate bonus
     *
     */
    int attack_speed;
    /**
     * @brief Nbr of bonus
     *
     */
    int nbr;
} stat_bonus_t;

/**
 * @brief Timer of the bonus
 */
typedef struct bonus_s {
    /**
     * @brief Timer of the bonuses
     *
     */
    std::vector<std::pair<std::chrono::time_point<std::chrono::steady_clock>, stat_bonus_t>> timer;
} bonus_t;

/**
 * @brief Spends a point to augment a player's stat
 *
 * @param world world to act on
 * @param msg The client's message
 * @param server The game's server
 */
void spend_point(World &world, ClientMessage msg, NetworkServer &server);

/**
 * @brief Augments a player's stat
 *
 * @param world world to act on
 * @param stat stat to augment
 * @param e Player's entity ID
 */
void stat_up(World &world, GameStat &stat, std::size_t &e);

/**
 * @brief Send stats to the player
 *
 * @param world world to act on
 * @param server The game's server
 * @param index Player's entity ID
 */
void send_stats_to_players(World &world, NetworkServer &server, std::size_t index);

/**
 * @brief Handles players' leveling up
 *
 * @param world world to act on
 * @param server The server
 *
 * @return Negative value in case of error
 */
int level_up_system(World &world, NetworkServer &server);

/**
 * @brief Handles the end of the game
 *
 * @param world world to act on
 * @param server The server
 *
 * @return Negative value in case of error
 */
int end_game_system(World &world, NetworkServer &server);
