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

static std::map<sf::Keyboard::Key, Vector2i> key_to_direction = {
    {sf::Keyboard::Z, {0, -1}}, {sf::Keyboard::S, {0, 1}}, {sf::Keyboard::Q, {-1, 0}}, {sf::Keyboard::D, {1, 0}}};

static std::map<sf::Keyboard::Key, bool> key_pressed = {
    {sf::Keyboard::Z, false}, {sf::Keyboard::S, false}, {sf::Keyboard::Q, false}, {sf::Keyboard::D, false}};

void handle_movement(World &world, NetworkClient &client, sf::Event event)
{
    Message<GameMessage> moveMsg;
    moveMsg.header.id = GameMessage::C2S_MOVEMENT;
    Vector2i current_direction = world.getDirection();
    Vector2i new_direction = {0, 0};

    if (event.type == sf::Event::KeyPressed)
        key_pressed[event.key.code] = true;
    if (event.type == sf::Event::KeyReleased)
        key_pressed[event.key.code] = false;
    for (auto &key : key_pressed)
        if (key.second)
            new_direction += key_to_direction[key.first];
    if (new_direction != current_direction) {
        moveMsg << new_direction;
        client.send(moveMsg);
        world.setDirection(new_direction);
    }
}
