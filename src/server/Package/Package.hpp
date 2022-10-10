/**
 * @file package.hpp
 * @author your name (you@domain.com)
 * @brief package interface
 * @version 0.1
 * @date 2022-10-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>

class IPacket {
  public:
    virtual void send() = 0;
};

class APacket : public IPacket {
  public:
    virtual void send() = 0;

  protected:
    std::string _type;
    int _length;
    std::string _content;
};