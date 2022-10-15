/**
 * @file IPackage.hpp
 * @author Louis Maestre (louis.maestre@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-10-11
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

class IPacket {
  public:
    virtual void send() = 0;
};