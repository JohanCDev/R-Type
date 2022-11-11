/**
 * @file MessageType.hpp
 * @author Tanguy Bellicha (tanguy.bellicha@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-10-16
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

/**
 * @brief Enumerate packets types
 *
 */
enum class GameMessage : uint32_t {
    C2S_JOIN,
    C2S_LEAVE,
    C2S_SHOOT,
    C2S_MOVEMENT,
    C2S_START_GAME,
    C2S_SELECT_SHIP,
    S2C_ENTITY_NEW,
    S2C_ENTITY_DEAD,
    S2C_GAME_END,
    S2C_MOVEMENT,
    S2C_ENTITY_HIT,
    S2C_WAVE_STATUS,
    S2C_OK,
    S2C_START_GAME,
    S2C_PLAYERS_IN_LOBBY,
    S2C_PLAYERS_READY,
    S2C_UPDATE_POSITION
};

/**
 * @brief Enumerate status of waves
 *
 */
enum class WaveStatus : uint32_t { START, BOSS_START, END };

/**
 * @brief Enumerate objects of the game
 *
 */
enum class GameObject : uint32_t {
    LASER,
    PLAYER,
    BOSS_1,
    ENEMY_FOCUS,
    ENEMY_SNIPER,
    ENEMY_ODD,
    GAME_OBJECT_COUNT,
    SHIP_ARMORED,
    SHIP_DAMAGE,
    SHIP_ENGINEER,
    SHIP_SNIPER
};
