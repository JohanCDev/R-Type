/**
 * @file S2C_Error.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-10-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "Package.hpp"

class S2C_ERROR : public APacket {
  public:
    void send() {
      std::cout << "S2C Error" << std::endl;
    }
};