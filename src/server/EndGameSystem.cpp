/**
 * @file EndGameSystem.cpp
 * @author Adam Djebar (adam.djebar@epitech.eu)
 * @brief Main file of the server
 * @version 0.1
 * @date 2022-11-13
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "../ECS/Components/AllComponents.hpp"
#include "../ECS/World.hpp"

int end_game_system(World &world, NetworkServer &server)
{
    auto &clients = world.getRegistry().get_components<ClientIDComponent>();

    int alivePlayers = 0;

    for (auto& client : clients) {
        if (client && client.has_value())
            alivePlayers++;
    }
    if (!alivePlayers) {
        Message<GameMessage> msg;

        msg.header.id = GameMessage::S2C_GAME_END;
        msg << "end";
        server.SendToAll(msg);
        world.state = GameState::Over;
    }
    return 0;
}
