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
#include "server.hpp"

#include "../Common/Message/Message.hpp"
#include "../Common/Message/MessageType.hpp"
#include "../ECS/Registry.hpp"
#include "../ECS/ResourcesManager.hpp"
#include "../ECS/SparseArray.hpp"
#include "../ECS/Components/AllComponents.hpp"
#include "../ECS/Entity.hpp"

// int velocity_system(registry &r, ResourcesManager manager, sf::Clock clock);
// int shooting_system(registry &r, ResourcesManager manager, sf::Clock clock);

int main()
{
    NetworkServer server(60000);
    // registry r;
    // ResourcesManager manager;

    // r.register_components<DrawableComponent>();
    // r.register_components<DestroyableComponent>();
    // r.register_components<PositionComponent>();
    // r.register_components<VelocityComponent>();
    // r.register_components<ImmobileComponent>();
    // r.register_components<ControllableComponent>();
    // r.register_components<CollideComponent>();
    // r.register_components<WeaponComponent>();
    // r.register_components<HealthComponent>();

    // r.register_systems(&shooting_system);
    // r.register_systems(&velocity_system);

    while (1) {
        while (server.HasMessages()) {
            // std::string txt = server.PopMessage().first;
            // std::cout << txt << std::endl;

            Message<GameMessage> gameMsg = server.PopMessage().first;

            std::string tmp(gameMsg.body.begin(), gameMsg.body.end());

            switch (gameMsg.header.id) {
                case (GameMessage::C2S_JOIN): std::cout << "User Joined with message:" << tmp << std::endl; break;
                case (GameMessage::C2S_LEAVE): std::cout << "User Left with message:" << tmp << std::endl; break;
                default: std::cout << "Unkown Message" << std::endl; break;
            }

            if (tmp == "bye") {
                break;
            }
            // for (auto &system : r.get_systems()) {
            //     system(r, manager, clock);
            // }
        };
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    }
    return 0;
}
