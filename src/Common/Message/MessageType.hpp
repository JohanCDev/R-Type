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

enum class GameMessage : uint32_t {
    C2S_JOIN,
    C2S_LEAVE,
    C2S_SHOOT,
    C2S_MOVEMENT,
    S2C_ENTITY_NEW,
    S2C_ENTITY_DEAD,
    S2C_GAME_END,
    S2C_MOVEMENT,
    S2C_ENTITY_HIT,
    S2C_OK
};

enum class GameObject : uint32_t { LASER, PLAYER, ENEMY_FOCUS, ENEMY_SNIPER, ENEMY_ODD, GAME_OBJECT_COUNT };
