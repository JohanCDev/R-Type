/**
 * @file main.cpp
 * @author Cédric Corge (cedric.corge@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-10-16
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
#include "client.hpp"

#include "../ECS/World.hpp"

int main(void)
{
    unsigned short port;
    std::cin >> port;
    NetworkClient client("localhost", "60000", port);
    World world(sf::VideoMode(1920, 1080), "My window");

    std::srand(std::time(NULL));

    world.register_all_component();
    world.register_all_system();
    world.register_all_assets();
    world.register_all_drawable_object();
    
    world.create_player(GameObject::PLAYER, Vector2f{20.0, 20.0}, Vector2i{5, 5}, 0.2);

    Message<GameMessage> hiMsg;
    hiMsg.header.id = GameMessage::C2S_JOIN;
    hiMsg << "Lezgongue";

    Message<GameMessage> byeMsg;
    byeMsg.header.id = GameMessage::C2S_LEAVE;
    byeMsg << "Bybye";


    client.send(hiMsg);
    while (world.getWindow().isOpen()) {
        while (client.HasMessages()) {
            Message<GameMessage> msg = client.PopMessage();

            client.processMessage(msg, world);
        }
        sf::Event event;
        while (world.getWindow().pollEvent(event)) {
            // "close requested" event: we close the window
            if (controllable_system(world, event) == 1)
                continue;
            if (event.type == sf::Event::Closed)
                world.getWindow().close();
        }

        world.getWindow().clear(sf::Color::Black);
        for (auto &system: world.getRegistry().get_systems()) {
            system(world);
        }
        world.getWindow().display();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    client.send(byeMsg);
    return 0;
}
