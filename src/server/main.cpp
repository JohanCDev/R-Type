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

/**
 * @brief Define the WIN32 version
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
    {GameMessage::C2S_MOVEMENT, player_moved}, {GameMessage::C2S_SHOOT, player_shot},
    {GameMessage::C2S_START_GAME, start_game}, {GameMessage::C2S_SELECT_SHIP, select_ship},
    {GameMessage::C2S_SPEND_POINT, spend_point}};

/**
 * @brief Main function
 *
 * @return int
 */
int main()
{
    NetworkServer server(60000);
    World world;
    world.state = GameState::Lobby;
    srand(time(NULL));
    waves_t waves = {false, 0, DEFAULT_WAVE_DIFFICULTY, DEFAULT_WAVE_DIFFICULTY, sf::Clock()};
    bool adapt_difficulty = true;
    sf::Clock refreshClock;

    world.register_all_drawable_object();
    bonus_t bonus_stat;

    while (1) {
        while (server.HasMessages()) {
            ClientMessage msg = server.PopMessage();
            if (mapFunc.contains(msg.first.header.id))
                mapFunc[msg.first.header.id](world, msg, server);
        };
        switch (world.state) {
            case GameState::Lobby: lobby_system(world, server); break;
            case GameState::Playing:
                if (adapt_difficulty) {
                    adapt_difficulty = false;
                    waves.base_difficulty = DEFAULT_WAVE_DIFFICULTY * server.clients.size();
                    waves.remaining_difficulty = waves.base_difficulty;
                }
                if (refreshClock.getElapsedTime().asSeconds() > 0.2f) {
                    refresh_system(world, server);
                    refreshClock.restart();
                }
                velocity_system(world);
                collide_system(world, server);
                wave_system(world, server, waves);
                ia_system(world, server);
                bonus_system(world, server, bonus_stat);
                destroy_outdated_entities(world, server);
                end_game_system(world, server);
                break;
            default: break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    return 0;
}
