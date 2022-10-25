/**
 * @file loop.cpp
 * @author Tanguy BELLICHA (tanguy.bellicha@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-10-11
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <ctime>
#include "../Common/Message/Message.hpp"
#include "../Common/Message/MessageType.hpp"
#include "../ECS/Components/AllComponents.hpp"
#include "../ECS/Entity.hpp"
#include "../ECS/Registry.hpp"
#include "../ECS/ResourcesManager.hpp"
#include "../ECS/SparseArray.hpp"
#include "../ECS/World.hpp"
#include "game.hpp"

void player_joined(World &world, ClientMessage msg, NetworkServer &server)
{
    size_t id = 0;
    id = world.create_player("", Vector4(375, 6, 21, 24), DEFAULT_PLAYER_SCALE, DEFAULT_PLAYER_SCALE,
        DEFAULT_PLAYER_POS_X, DEFAULT_PLAYER_POS_Y, DEFAULT_PLAYER_HP, 0, 0, 0.2, DEFAULT_KEY_TOP, DEFAULT_KEY_BOT,
        DEFAULT_KEY_RGT, DEFAULT_KEY_LFT, DEFAULT_KEY_SHOOT);
    world.getRegistry().add_component<ClientIDComponent>(
        world.getRegistry().entity_from_index(id), ClientIDComponent(msg.second));
}

void player_left(World &world, ClientMessage msg, NetworkServer &server)
{
    std::cout << "Player Left" << std::endl;
    (void)world;
}

void player_moved(World &world, ClientMessage msg, NetworkServer &server)
{
    sf::Vector2f move;
    registry &r = world.getRegistry();
    sparse_array<VelocityComponent> &velocity = r.get_components<VelocityComponent>();
    sparse_array<ClientIDComponent> &clients = r.get_components<ClientIDComponent>();
    std::size_t index = 0;
    msg.first >> move;

    for (auto &i : clients) {
        if (i && i.has_value()) {
            if (i.value().id == msg.second) {
                velocity[index]->x = move.x * DEFAULT_PLAYER_SPD;
                velocity[index]->y = move.y * DEFAULT_PLAYER_SPD;
            }
        }
        index++;
    }
}

void player_shot(World &world, ClientMessage msg, NetworkServer &server)
{
    std::cout << "Player Shot" << std::endl;
    world.create_laser(1, 1, DEFAULT_LASER_X_SPD, DEFAULT_LASER_Y_SPD, 0.2, 0);
}

void create_enemy(World &world, NetworkServer &server)
{
    (void)server;
    int random_y = rand() % 400 + 51;
    Message<GameMessage> msg;
    msg.header.id = GameMessage::S2C_ENTITY_NEW;
    msg << EntityCode::ENEMY;
    msg << sf::Vector2f(0, random_y);
    world.create_enemy("r-typesheet39.gif", Vector4(34, 2, 64, 64), DEFAULT_ENEMY_SCALE, DEFAULT_ENEMY_SCALE, 0,
        random_y, DEFAULT_ENEMY_SPD, DEFAULT_ENEMY_SPD, 0.2, 0);
    // server.SendToAll(msg);
}
