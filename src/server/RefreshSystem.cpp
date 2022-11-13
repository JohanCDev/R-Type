/**
 * @file RefreshSystem.cpp
 * @author Adam Djebar (adam.djebar@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-11-11
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "../ECS/World.hpp"
#include "server.hpp"

#include <iostream>

int refresh_system(World &world, NetworkServer &server)
{
    auto &positions = world.getRegistry().get_components<PositionComponent>();
    auto &ids = world.getRegistry().get_components<EntityIDComponent>();
    Message<GameMessage> msg;

    std::size_t index = 0;
    for (auto &pos : positions) {
        if (pos && pos.has_value()) {
            auto &id = ids[index];
            if (!(id && id.has_value()))
                continue;
            msg.header.id = GameMessage::S2C_UPDATE_POSITION;
            msg << pos.value();
            msg << id.value();
            server.SendToAll(msg);
        }
        index++;
    }
    return 0;
}
