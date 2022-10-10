/**
 * @file S2C_EntityDead.hpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-10-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "../Package.hpp"

class S2C_ENTITY_DEAD : public APacket {
  public:
    void send()
    {
        std::cout << "S2C dead entity" << std::endl;
    }
};