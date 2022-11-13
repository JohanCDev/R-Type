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
    C2S_SPEND_POINT,
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
    S2C_UPDATE_POSITION,
    S2C_LEVEL_UP,
    S2C_UPDATE_STATS,
    S2C_BONUS_DEAD,
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
    LASER_ENEMY,
    PLAYER,
    SHIP_ARMORED,
    SHIP_DAMAGE,
    SHIP_ENGINEER,
    SHIP_SNIPER,
    BOSS_1,
    ENEMY_FOCUS,
    ENEMY_KAMIKAZE,
    ENEMY_SNIPER,
    BONUS_ATTACK,
    BONUS_ATTACK_SPEED,
    BONUS_HEAL,
    BONUS_SPEED,
    BONUS_DOUBLE
};

/**
 *  @brief Enumerate game stats
 *
 */
enum class GameStat : uint32_t { HEALTH, DAMAGE, SPD, ATK_SPD, DOUBLE };
