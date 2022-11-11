/**
 * @file send_stats_to_players.cpp
 * @author Adam Djebar (adam.djebar@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-11-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "../ECS/Components/AllComponents.hpp"
#include "../ECS/World.hpp"

void send_stats_to_players(World &world, NetworkServer &server, std::size_t index)
{
    auto &health = world.getRegistry().get_components<HealthComponent>()[index];
    auto &weapon = world.getRegistry().get_components<WeaponComponent>()[index];
    //auto &max_spd = world.getRegistry().get_components<MaximumVelocityComponent>()[index];
    auto &entityId = world.getRegistry().get_components<EntityIDComponent>()[index];
    Message<GameMessage> msg;

    if (entityId && entityId.has_value()) {
        msg.header.id = GameMessage::S2C_UPDATE_STATS;
        if (!(health && health.has_value())) 
            return;
        msg << health;
        if (!(weapon && weapon.has_value()))
            return;
        msg << weapon;
        //if (!(max_spd && max_spd.has_value()))
        //    return;
        //msg << max_spd;
        msg << entityId->id;
        server.SendToAll(msg);
    }
}
