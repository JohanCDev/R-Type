/**
 * @file package.hpp
 * @author Louis Maestre (louis.maestre@epitech.eu)
 * @brief package interface
 * @version 0.1
 * @date 2022-10-05
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <iostream>
#include "IPackage.hpp"

class APacket : public IPacket {
  public:
    virtual void send() = 0;

  protected:
    std::string _type;
    int _length;
    std::string _content;
};