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

#include <iostream>
#include <thread>
#include "../Common/Message/Message.hpp"
#include "../Common/Message/MessageType.hpp"
#include "../ECS/Systems/AllSystem.hpp"
#include "../ECS/World.hpp"
#include "game.hpp"
#include "server.hpp"

static std::map<GameMessage, std::function<void(World &, ClientMessage, NetworkServer &)>> mapFunc = {
    {GameMessage::C2S_JOIN, player_joined}, {GameMessage::C2S_LEAVE, player_left},
    {GameMessage::C2S_MOVEMENT, player_moved}, {GameMessage::C2S_SHOOT, player_shot}};

int main()
{
    NetworkServer server(60000);
    World world;
    srand(time(NULL));
    waves_t waves = {false, 0, DEFAULT_WAVE_DIFFICULTY, DEFAULT_WAVE_DIFFICULTY, sf::Clock()};

    world.register_all_component();
    world.register_all_drawable_object();
    int i = 0;

    while (1) {
        while (server.HasMessages()) {
            ClientMessage msg = server.PopMessage();
            mapFunc[msg.first.header.id](world, msg, server);
        };
        // auto end = std::chrono::steady_clock::now();
        // double elapsed_time_ns = double(std::chrono::duration_cast<std::chrono::seconds>(end - start).count());
        // if (elapsed_time_ns >= 1.0) {
        //     start = std::chrono::steady_clock::now();
        //     std::cout << i++ << " secondes écoulées" << std::endl;
        // }
        velocity_system(world);
        shooting_system(world, server);
        ia_system(world, server);
        wave_system(world, server, waves);
        bonus_system(world, server);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    return 0;
}
