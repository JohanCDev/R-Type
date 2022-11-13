/**
 * @file DestroyOutdatedEntities.cpp
 * @author Cédric Corge (cedric.corge@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-11-13
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "../ECS/World.hpp"
#include "server.hpp"

void destroy_outdated_entities(World &world, NetworkServer &server)
{
    auto &drawables = world.getRegistry().get_components<DrawableComponent>();
    auto &positions = world.getRegistry().get_components<PositionComponent>();
    auto &entityId = world.getRegistry().get_components<EntityIDComponent>();
    Message<GameMessage> sending_msg;

    for (size_t i = 0; i < drawables.size(); ++i) {
        if (drawables[i] && drawables[i].has_value()) {
            if (positions[i]->pos.x < -400 || positions[i]->pos.x > 2200) {
                sending_msg.header.id = GameMessage::S2C_ENTITY_DEAD;
                sending_msg << entityId[i]->id;
                world.getRegistry().kill_entity(world.getRegistry().entity_from_index(i));
                server.SendToAll(sending_msg);
            }
        }
    }
}