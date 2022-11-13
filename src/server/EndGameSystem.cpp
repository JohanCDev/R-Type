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

int end_game_system(World &world, NetworkServer &server, waves_t &waves)
{
    auto &clients = world.getRegistry().get_components<ClientIDComponent>();

    int alivePlayers = 0;

    for (auto &client : clients) {
        if (client && client.has_value())
            alivePlayers++;
    }
    if (!alivePlayers) {
        Message<GameMessage> msg;

        msg.header.id = GameMessage::S2C_GAME_END;
        msg << "end";
        server.SendToAll(msg);
        auto &drawables = world.getRegistry().get_components<DrawableComponent>();
        auto &entityId = world.getRegistry().get_components<EntityIDComponent>();
        for (size_t i = 0; i < drawables.size(); i++) {
            if (drawables[i] && drawables[i].has_value()) {
                world.getRegistry().kill_entity(world.getRegistry().entity_from_index(i));
                msg.header.id = GameMessage::S2C_ENTITY_DEAD;
                msg << entityId[i]->id;
                server.SendToAll(msg);
            }
        }
        waves = {false, 0, DEFAULT_WAVE_DIFFICULTY, DEFAULT_WAVE_DIFFICULTY, sf::Clock()};
        world.player_ships.clear();
        world.state = GameState::Lobby;
    }
    return 0;
}
