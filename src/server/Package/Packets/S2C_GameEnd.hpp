/**
 * @file S2C_GameEnd.hpp
 * @author Louis Maestre (louis.maestre@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-10-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "../APackage.hpp"

class S2C_GAME_END : public APacket {
  public:
    void send()
    {
        std::cout << "S2C end game" << std::endl;
    }
};