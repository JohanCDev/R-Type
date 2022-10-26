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

void handle_movement(World &world, NetworkClient &client, sf::Event event);

int main(void)
{
    unsigned short port;
    // std::cin >> port;
    NetworkClient client("localhost", "60000", port);
    World world(sf::VideoMode(800, 600), "My window");

    std::srand(std::time(NULL));

    world.register_all_component();
    world.register_all_system();
    world.register_all_assets();
    world.register_all_drawable_object();
    world.getRegistry().register_systems(&drawable_system);

    Message<GameMessage> hiMsg;
    hiMsg.header.id = GameMessage::C2S_JOIN;
    hiMsg << "Lezgongue";

    Message<GameMessage> byeMsg;
    byeMsg.header.id = GameMessage::C2S_LEAVE;
    byeMsg << "Bybye";

    Message<GameMessage> shootMsg;
    shootMsg.header.id = GameMessage::C2S_SHOOT;
    shootMsg << "Shoot";

    client.send(hiMsg);
    while (world.getWindow().isOpen()) {
        while (client.HasMessages()) {
            Message<GameMessage> msg = client.PopMessage();

            client.processMessage(msg, world);
        }
        sf::Event event;
        while (world.getWindow().pollEvent(event)) {
            handle_movement(world, client, event);
            if (event.type == sf::Event::MouseButtonPressed && (MouseInput)event.mouseButton.button == MouseInput::Left_click) {
                client.send(shootMsg);
            }
            if (event.type == sf::Event::Closed)
                world.getWindow().close();
        }

        world.getWindow().clear(sf::Color::Black);
        for (auto &system: world.getRegistry().get_systems()) {
            system(world);
        }
        world.getWindow().display();

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    client.send(byeMsg);
    return 0;
}
