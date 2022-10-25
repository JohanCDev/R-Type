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

enum class GameMessage { C2S_JOIN, C2S_LEAVE, S2C_ENTITY_NEW };

enum class GameObject { LASER = 0, PLAYER, ENEMY };