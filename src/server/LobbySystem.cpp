/**
 * @file main.cpp
 * @author Adam Djebar (adam.djebar@epitech.eu)
 * @brief Main file of the server
 * @version 0.1
 * @date 2022-11-06
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "../ECS/World.hpp"
#include "server.hpp"

int lobby_system(World &world, NetworkServer &server)
{
    Message<GameMessage> player_msg;
    Message<GameMessage> ready_msg;
    std::size_t nbr = server.clients.size();

    player_msg.header.id = GameMessage::S2C_PLAYERS_IN_LOBBY;
    player_msg << nbr;
    server.SendToAll(player_msg);

    ready_msg.header.id = GameMessage::S2C_PLAYERS_READY;
    if (world.player_ships.size() == server.clients.size()) {
        ready_msg << true;
    } else {
        ready_msg << false;
    }
    server.SendToAll(ready_msg);
    return 0;
}
