/**
 * @file VelocitySystem.cpp
 * @author Cédric Corge (cedric.corge@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-10-16
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "../Components/AllComponents.hpp"
#include "../Registry.hpp"
#include "../ResourcesManager.hpp"
#include "../World.hpp"

int velocity_system(World &world)
{
    registry &r = world.getRegistry();
    sparse_array<VelocityComponent> &velocity = r.get_components<VelocityComponent>();
    sparse_array<PositionComponent> &position = r.get_components<PositionComponent>();

    std::size_t index = 0;

    for (auto &i : velocity) {
        if (i && i.has_value()) {
            sf::Time elapsedTime = world.getClock().getElapsedTime();
            if (elapsedTime.asSeconds() > i->seconds) {
                position[index]->pos.x += i->speed.x;
                position[index]->pos.y += i->speed.y;
                i->seconds += i->coeff;
            }
        }
        index++;
    }
    return (0);
}
