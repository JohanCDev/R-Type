/**
 * @file Package.hpp
 * @author your name (you@domain.com)
 * @brief RFC class
 * @version 0.1
 * @date 2022-10-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef PACKAGE_HPP_
#define PACKAGE_HPP_

#include <iostream>

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

class S2C_OK : public APacket {
  public:
    void send() {
      std::cout << "S2C OK" << std::endl;
    }
};

class S2C_ERROR : public APacket {
  public:
    void send() {
      std::cout << "S2C Error" << std::endl;
    }
};

class S2C_MOVEMENT : public APacket {
  public:
    void send() {
      std::cout << "S2C Movement" << std::endl;
    }
};

class S2C_ENTITY_NEW : public APacket {
  public:
    void send() {
      std::cout << "S2C New Entity" << std::endl;
    }
};

class S2C_ENTITY_DEAD : public APacket {
  public:
    void send() {
      std::cout << "S2C dead entity" << std::endl;
    }
};

class S2C_ENTITY_HIT : public APacket {
  public:
    void send() {
      std::cout << "S2C hit entity" << std::endl;
    }
};

class S2C_GAME_END : public APacket {
  public:
    void send() {
      std::cout << "S2C end game" << std::endl;
    }
};

#endif /* !PACKAGE_HPP_ */
