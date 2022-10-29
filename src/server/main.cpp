/**
 * @file main.cpp
 * @author Johan Chrillesen (johan.chrillesen@epitech.eu)
 * @brief Main file of the server
 * @version 0.1
 * @date 2022-09-20
 *
 * @copyright Copyright (c) 2022
 *
 */

#define _WIN32_WINNT 0x0601

#include <chrono>
#include <iostream>
#include <thread>
#include "../Common/Message/Message.hpp"
#include "../Common/Message/MessageType.hpp"
#include "../ECS/World.hpp"
#include "../ECS/Systems/AllSystem.hpp"
#include "game.hpp"
#include "server.hpp"

static std::map<GameMessage, std::function<void(World &, ClientMessage, NetworkServer &)>> mapFunc =
{
    {GameMessage::C2S_JOIN, player_joined},
    {GameMessage::C2S_LEAVE, player_left},
    {GameMessage::C2S_MOVEMENT, player_moved},
    {GameMessage::C2S_SHOOT, player_shot}
};

int main()
{
    NetworkServer server(60000);
    World world;
    sf::Clock rand_enemies_clock;
    srand(time(NULL));

    world.register_all_component();
    world.register_all_system();
    bool a = false;

    while (1) {
        while (server.HasMessages()) {
            ClientMessage msg = server.PopMessage();
            mapFunc[msg.first.header.id](world, msg, server);
        };
        if (rand_enemies_clock.getElapsedTime().asMilliseconds() > 5000) {
            if (a == false) {
                create_enemy(world, server);
                rand_enemies_clock.restart();
                a = true;
            }
        }
        for (auto &system: world.getRegistry().get_systems())
            system(world);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    return 0;
}
