/**
 * @file S2C_Ok.hpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-10-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "../APackage.hpp"

class S2C_OK : public APacket {
  public:
    void send()
    {
        std::cout << "S2C OK" << std::endl;
    }
};