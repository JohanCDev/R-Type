/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Package
*/

#ifndef PACKAGE_HPP_
#define PACKAGE_HPP_

#include <iostream>
#include "server.hpp"

enum Type { Join, Movement, Shoot, Leave };

class IPacket {
  public:
    virtual void send() = 0;
};

class APacket : public IPacket {
  public:
    virtual void send() = 0;

  protected:
    Type _type;
    int _length;
    std::string _content;
};

class Packet : public APacket {

};

class S2C_OK : public APacket {
  public:
    void send() {
      std::cout << "S2C OK mgl" << std::endl;
    }
};

class S2C_ERROR : public APacket {
  public:
    void send();
};

class S2C_MOVEMENT : public APacket {
  public:
    void send();
};

class S2C_ENTITY_NEW : public APacket {
  public:
    void send();
};

class S2C_ENTITY_DEAD : public APacket {
  public:
    void send();
};

class S2C_ENTITY_HIT : public APacket {
  public:
    void send();
};

class S2C_GAME_END : public APacket {
  public:
    void send();
};

#endif /* !PACKAGE_HPP_ */
