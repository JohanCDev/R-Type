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
    size_t entity_id = 0;
    Message<GameMessage> sending_msg;

    entity_id = world.create_player("", Vector4i(375, 6, 21, 24), Vector2f(DEFAULT_PLAYER_SCALE, DEFAULT_PLAYER_SCALE),
        Vector2i{DEFAULT_PLAYER_POS_X, DEFAULT_PLAYER_POS_Y}, DEFAULT_PLAYER_HP, Vector2i{0, 0}, 0.2, DEFAULT_KEY_TOP,
        DEFAULT_KEY_BOT, DEFAULT_KEY_RGT, DEFAULT_KEY_LFT, DEFAULT_KEY_SHOOT);
    world.getRegistry().add_component<ClientIDComponent>(
        world.getRegistry().entity_from_index(entity_id), ClientIDComponent{msg.second});
    world.getRegistry().add_component<EntityIDComponent>(
        world.getRegistry().entity_from_index(entity_id), EntityIDComponent{entity_id});
    std::cout << "Player[" << msg.second << "]: joined the game" << std::endl;
    sending_msg.header.id = GameMessage::S2C_ENTITY_NEW;
    sending_msg << GameObject::PLAYER;
    sending_msg << entity_id;
    sending_msg << Vector2f{DEFAULT_PLAYER_POS_X, DEFAULT_PLAYER_POS_Y};
    server.SendToAll(sending_msg);
}

void player_left(World &world, ClientMessage msg, NetworkServer &server)
{
    registry &r = world.getRegistry();
    sparse_array<ClientIDComponent> &clients = r.get_components<ClientIDComponent>();
    sparse_array<EntityIDComponent> &entities = r.get_components<EntityIDComponent>();
    Message<GameMessage> sending_msg;
    size_t index = 0;

    std::cout << "Player[" << msg.second << "]: left the game" << std::endl;
    for (auto &i : clients) {
        if (i && i.has_value() && i.value().id == msg.second) {
            r.kill_entity(r.entity_from_index(index));
            sending_msg.header.id = GameMessage::S2C_ENTITY_DEAD;
            sending_msg << entities[index]->id;
            server.SendToAll(sending_msg);
            break;
        }
        index++;
    }
}

void player_moved(World &world, ClientMessage msg, NetworkServer &server)
{
    Vector2i move{0, 0};
    registry &r = world.getRegistry();
    sparse_array<VelocityComponent> &velocity = r.get_components<VelocityComponent>();
    sparse_array<ClientIDComponent> &clients = r.get_components<ClientIDComponent>();
    std::size_t index = 0;
    Message<GameMessage> sending_msg;

    msg.first >> move;
    for (auto &i : clients) {
        if (i && i.has_value()) {
            if (i.value().id == msg.second) {
                velocity[index]->speed.x = move.x * DEFAULT_PLAYER_SPD;
                velocity[index]->speed.y = move.y * DEFAULT_PLAYER_SPD;
                std::cout << "Player[" << msg.second << "]: Velocity{" << move.x * DEFAULT_PLAYER_SPD << ", "
                          << move.y * DEFAULT_PLAYER_SPD << "}" << std::endl;
                sending_msg.header.id = GameMessage::S2C_MOVEMENT;
                sending_msg << move;
                server.SendToAll(sending_msg);
                break;
            }
        }
        index++;
    }
}

void player_shot(World &world, ClientMessage msg, NetworkServer &server)
{
    registry &r = world.getRegistry();
    sparse_array<PositionComponent> &position = r.get_components<PositionComponent>();
    sparse_array<ClientIDComponent> &clients = r.get_components<ClientIDComponent>();
    std::size_t index = 0;
    Message<GameMessage> sending_msg;
    size_t entity_id = 0;

    for (auto &i : clients) {
        if (i && i.has_value()) {
            if (i.value().id == msg.second) {
                entity_id = world.create_laser(
                    Vector2i{position[index]->pos.x, position[index]->pos.y}, Vector2i{DEFAULT_LASER_SPD, 0}, 0.2, 0);
                std::cout << "Player[" << msg.second << "]: shot from Position{" << position[index]->pos.x << ", "
                          << position[index]->pos.y << "}" << std::endl;
                sending_msg.header.id = GameMessage::S2C_ENTITY_NEW;
                sending_msg << GameObject::LASER;
                sending_msg << entity_id;
                sending_msg << Vector2f{position[index]->pos.x, position[index]->pos.y};
                break;
            }
        }
        index++;
    }
}

void create_enemy(World &world, NetworkServer &server)
{
    size_t entity_id = 0;
    int random_y = rand() % 400 + 51;
    Message<GameMessage> sending_msg;

    entity_id = world.create_enemy("r-typesheet39.gif", Vector4i(34, 2, 64, 64),
        Vector2f(DEFAULT_ENEMY_SCALE, DEFAULT_ENEMY_SCALE), Vector2i{0, random_y},
        Vector2i{DEFAULT_ENEMY_SPD, DEFAULT_ENEMY_SPD}, 0.2, 0);
    world.getRegistry().add_component<EntityIDComponent>(
        world.getRegistry().entity_from_index(entity_id), EntityIDComponent{entity_id});
    std::cout << "Enemy[" << entity_id << "]: created at Position{840, " << random_y << "}" << std::endl;
    sending_msg.header.id = GameMessage::S2C_ENTITY_NEW;
    sending_msg << GameObject::ENEMY;
    sending_msg << entity_id;
    sending_msg << Vector2f(0, random_y);
    server.SendToAll(sending_msg);
}
