/**
 * @file handle_movement.cpp
 * @author Cédric CORGE (cedric.corge@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-10-26
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "../ECS/World.hpp"
#include "client.hpp"

void cancel_movement(World &world, NetworkClient &client, sf::Event event)
{
    Message<GameMessage> moveMsg;
    moveMsg.header.id = GameMessage::C2S_MOVEMENT;
    Vector2i current_direction = world.getDirection();

    if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Z) {
        moveMsg << Vector2i{current_direction.x, 0};
        client.send(moveMsg);
        world.setDirection({current_direction.x, 0});
    }
    if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::S) {
        moveMsg << Vector2i{current_direction.x, 0};
        client.send(moveMsg);
        world.setDirection({current_direction.x, 0});
    }
    if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Q) {
        moveMsg << Vector2i{0, current_direction.y};
        client.send(moveMsg);
        world.setDirection({0, current_direction.y});
    }
    if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::D) {
        moveMsg << Vector2i{0, current_direction.y};
        client.send(moveMsg);
        world.setDirection({0, current_direction.y});
    }
}

void handle_movement(World &world, NetworkClient &client, sf::Event event)
{
    Message<GameMessage> moveMsg;
    moveMsg.header.id = GameMessage::C2S_MOVEMENT;
    Vector2i current_direction = world.getDirection();

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Z) {
        if (current_direction.y != 1) {
            moveMsg << Vector2i{current_direction.x, 1};
            client.send(moveMsg);
            world.setDirection({current_direction.x, 1});
        }
    }
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S) {
        if (current_direction.y != -1) {
            moveMsg << Vector2i{current_direction.x, -1};
            client.send(moveMsg);
            world.setDirection({current_direction.x, -1});
        }
    }
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q) {
        if (current_direction.x != -1) {
            moveMsg << Vector2i{-1, current_direction.y};
            client.send(moveMsg);
            world.setDirection({-1, current_direction.y});
        }
    }
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D) {
        if (current_direction.x != 1) {
            moveMsg << Vector2i{1, current_direction.y};
            client.send(moveMsg);
            world.setDirection({1, current_direction.y});
        }
    }
    cancel_movement(world, client, event);
}