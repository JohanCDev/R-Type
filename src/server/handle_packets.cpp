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
#include "../ECS/SparseArray.hpp"
#include "../ECS/World.hpp"
#include "game.hpp"

#include <ctime>

#define DEFAULT_PLAYER_POS_X 50
#define DEFAULT_PLAYER_POS_Y 200
#define DEFAULT_PLAYER_SPD   4
#define DEFAULT_PLAYER_HP    100
#define DEFAULT_PLAYER_SCALE 2.0
#define DEFAULT_LASER_X_SPD  5
#define DEFAULT_LASER_Y_SPD  0
#define DEFAULT_ENEMY_HP     100
#define DEFAULT_ENEMY_ATK    40
#define DEFAULT_ENEMY_SPD    6
#define DEFAULT_ENEMY_SCALE  1.0
#define DEFAULT_KEY_TOP      KeyboardInput::Z
#define DEFAULT_KEY_RGT      KeyboardInput::D
#define DEFAULT_KEY_BOT      KeyboardInput::S
#define DEFAULT_KEY_LFT      KeyboardInput::Q
#define DEFAULT_KEY_SHOOT    MouseInput::Left_click

void player_joined(World &world, ClientMessage msg, NetworkServer &server)
{
    size_t entity_id = 0;
    Message<GameMessage> sending_msg;

    entity_id = world.create_player(
        GameObject::PLAYER, Vector2f{DEFAULT_PLAYER_POS_X, DEFAULT_PLAYER_POS_Y}, Vector2i{0, 0}, 0.2);
    world.getRegistry().add_component<ClientIDComponent>(
        world.getRegistry().entity_from_index(entity_id), ClientIDComponent{msg.second});
    world.getRegistry().add_component<EntityIDComponent>(
        world.getRegistry().entity_from_index(entity_id), EntityIDComponent{entity_id});
    std::cout << "Player[" << msg.second << "]: joined the game. Entity{" << entity_id << "}" << std::endl;
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

    for (auto &i : clients) {
        if (i && i.has_value() && i.value().id == msg.second) {
            r.kill_entity(r.entity_from_index(index));
            sending_msg.header.id = GameMessage::S2C_ENTITY_DEAD;
            sending_msg << entities[index]->id;
            server.SendToAll(sending_msg);
            std::cout << "Player[" << msg.second << "]: left the game" << std::endl;
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
    sparse_array<EntityIDComponent> &entities = r.get_components<EntityIDComponent>();
    std::size_t index = 0;
    Message<GameMessage> sending_msg;

    msg.first >> move;
    for (auto &i : clients) {
        if (i && i.has_value()) {
            if (i.value().id == msg.second) {
                velocity[index]->speed.x = move.x * DEFAULT_PLAYER_SPD;
                velocity[index]->speed.y = move.y * DEFAULT_PLAYER_SPD;
                std::cout << "Player[" << msg.second << "]: Velocity{" << velocity[index]->speed.x << ", "
                          << velocity[index]->speed.y << "}" << std::endl;
                sending_msg.header.id = GameMessage::S2C_MOVEMENT;
                sending_msg << entities[index]->id;
                sending_msg << velocity[index]->speed;
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
                entity_id = world.create_laser(GameObject::LASER,
                    Vector2f{position[index]->pos.x + 50, position[index]->pos.y}, Vector2i{DEFAULT_LASER_SPD, 0}, 0.2, 0);
                std::cout << "Player[" << msg.second << "]: shot from Position{" << position[index]->pos.x << ", "
                          << position[index]->pos.y << "}" << std::endl;
                sending_msg.header.id = GameMessage::S2C_ENTITY_NEW;
                sending_msg << GameObject::LASER;
                sending_msg << entity_id;
                sending_msg << Vector2f{position[index]->pos.x + 50, position[index]->pos.y};
                server.SendToAll(sending_msg);
                break;
            }
        }
        index++;
    }
}

void create_enemy(World &world, NetworkServer &server)
{
    size_t entity_id = 0;
    float random_y = rand() % 500 + 50;
    Message<GameMessage> sending_msg;

    entity_id = world.create_enemy(
        GameObject::ENEMY, Vector2f{0.0f, random_y}, Vector2i{DEFAULT_ENEMY_SPD, DEFAULT_ENEMY_SPD}, 0.2, 0);
    world.getRegistry().add_component<EntityIDComponent>(
        world.getRegistry().entity_from_index(entity_id), EntityIDComponent{entity_id});
    std::cout << "Enemy[" << entity_id << "]: created at Position{800, " << random_y << "}" << std::endl;
    sending_msg.header.id = GameMessage::S2C_ENTITY_NEW;
    sending_msg << GameObject::ENEMY;
    sending_msg << entity_id;
    sending_msg << Vector2f{800, random_y};
    server.SendToAll(sending_msg);
}
