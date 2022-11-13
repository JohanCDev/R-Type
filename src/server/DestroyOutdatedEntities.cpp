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

    for (size_t i = 0; i < drawables.size(); ++i) {
        if (drawables[i] && drawables[i].has_value()) {
            if (positions[i])
        }
    }
}