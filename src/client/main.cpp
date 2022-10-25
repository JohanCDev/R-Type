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

void cancel_movement(World &world, NetworkClient &client, sf::Event event)
{
    Message<GameMessage> moveMsg;
    moveMsg.header.id = GameMessage::C2S_MOVEMENT;
    Vector2f current_direction = world.getDirection();

    if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Z) {
        moveMsg << Vector2f{current_direction.x, 0};
        client.send(moveMsg);
        world.setDirection({current_direction.x, 0});
    }
    if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::S) {
        moveMsg << Vector2f{current_direction.x, 0};
        client.send(moveMsg);
        world.setDirection({current_direction.x, 0});
    }
    if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Q) {
        moveMsg << Vector2f{0, current_direction.y};
        client.send(moveMsg);
        world.setDirection({0, current_direction.y});
    }
    if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::D) {
        moveMsg << Vector2f{0, current_direction.y};
        client.send(moveMsg);
        world.setDirection({0, current_direction.y});
    }
}

void handle_movement(World &world, NetworkClient &client, sf::Event event)
{
    Message<GameMessage> moveMsg;
    moveMsg.header.id = GameMessage::C2S_MOVEMENT;
    Vector2f current_direction = world.getDirection();

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Z) {
        if (current_direction.y != 1) {
            moveMsg << Vector2f{current_direction.x, 1};
            client.send(moveMsg);
            world.setDirection({current_direction.x, 1});
        }
    }
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S) {
        if (current_direction.y != -1) {
            moveMsg << Vector2f{current_direction.x, -1};
            client.send(moveMsg);
            world.setDirection({current_direction.x, -1});
        }
    }
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q) {
        if (current_direction.x != -1) {
            moveMsg << Vector2f{-1, current_direction.y};
            client.send(moveMsg);
            world.setDirection({-1, current_direction.y});
        }
    }
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D) {
        if (current_direction.x != 1) {
            moveMsg << Vector2f{1, current_direction.y};
            client.send(moveMsg);
            world.setDirection({1, current_direction.y});
        }
    }
    cancel_movement(world, client, event);
}

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
    world.register_all_drawable_object();
    
    world.create_player(GameObject::PLAYER, Vector2f{20.0f, 20.0f}, Vector2i{0, 0}, 0.2f);

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

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    client.send(byeMsg);
    return 0;
}
