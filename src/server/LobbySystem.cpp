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

#include "server.hpp"
#include "../ECS/World.hpp"

int lobby_system(World &world, NetworkServer &server)
{
    Message<GameMessage> player_msg;
    Message<GameMessage> ready_msg;
    std::size_t nbr = server.clients.size();

    player_msg.header.id = GameMessage::S2C_PLAYERS_IN_LOBBY;
    //std::cout << nbr << std::endl;
    player_msg << nbr;
    server.SendToAll(player_msg);

    ready_msg.header.id = GameMessage::S2C_PLAYERS_READY;
    //std::cout << "Player ready: " << world.player_ships.size() << " " << "client number: " << server.clients.size() << std::endl;
    if (world.player_ships.size() == server.clients.size()) {
        ready_msg << true;
        server.SendToAll(ready_msg);
        std::cout << "ready" << std::endl;
    } else {
        ready_msg << false;
    }
    return 0;
}
