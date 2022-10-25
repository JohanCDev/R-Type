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
    World world(sf::VideoMode(800, 600), "My window");

    std::srand(std::time(NULL));

    world.register_all_component();
    world.register_all_system();
    world.register_all_assets();
    
    world.create_player("assets/r-typesheet5.gif", Vector4i{375, 6, 21, 24}, Vector2f(2.0, 2.0), Vector2i(20, 20), 3, Vector2i(5, 5), 0.2, KeyboardInput::Up, KeyboardInput::Down, KeyboardInput::Right, KeyboardInput::Left, MouseInput::Left_click);

    Message<GameMessage> hiMsg;
    hiMsg.header.id = GameMessage::C2S_JOIN;
    hiMsg << "Lezgongue";

    Message<GameMessage> byeMsg;
    byeMsg.header.id = GameMessage::C2S_LEAVE;
    byeMsg << "Bybye";

    while (world.getWindow().isOpen()) {
        while (client.HasMessages()) {
            Message<GameMessage> msg = client.PopMessage();

            //processMessage(msg);
        }
        sf::Event event;
        while (world.getWindow().pollEvent(event)) {
            // "close requested" event: we close the window
            if (controllable_system(world, event) == 1)
                continue;
            if (event.type == sf::Event::Closed)
                world.getWindow().close();
        }
        //client.send("hi");
        client.send(hiMsg);
        client.send(byeMsg);

        world.getWindow().clear(sf::Color::Black);
        for (auto &system: world.getRegistry().get_systems()) {
            system(world);
        }
        world.getWindow().display();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return 0;
}
