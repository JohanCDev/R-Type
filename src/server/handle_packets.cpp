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

void player_joined(World &world, ClientMessage msg, NetworkServer &server)
{
    size_t entity_id = 0;
    Message<GameMessage> sending_msg;

    entity_id = world.create_player(GameObject::PLAYER,
        Vector2f{defaultValues[GameObject::PLAYER].pos.x, defaultValues[GameObject::PLAYER].pos.y}, Vector2i{0, 0},
        0.04f);
    world.getRegistry().add_component<ClientIDComponent>(
        world.getRegistry().entity_from_index(entity_id), ClientIDComponent{msg.second});
    world.getRegistry().add_component<EntityIDComponent>(
        world.getRegistry().entity_from_index(entity_id), EntityIDComponent{entity_id});
    std::cout << "Player[" << msg.second << "]: joined the game. Entity{" << entity_id << "}" << std::endl;
    sending_msg.header.id = GameMessage::S2C_ENTITY_NEW;
    sending_msg << GameObject::PLAYER;
    sending_msg << entity_id;
    sending_msg << Vector2f{defaultValues[GameObject::PLAYER].pos.x, defaultValues[GameObject::PLAYER].pos.y};
    server.SendToAll(sending_msg);
}

void bonus_creation(World &world, NetworkServer &server, Vector2f pos)
{
    size_t entity_id = 0;
    Message<GameMessage> sending_msg;
    GameObject tmp;
    std::srand(std::time(nullptr));
    int random_variable = std::rand();
    // std::string bonus_name;
    Bonus bonus_name;

    if (random_variable % 3 == 0) {
        tmp = GameObject::BONUS;
        // bonus_name = "attack bonus";
        bonus_name = Bonus::ATTACK;
    } else if (random_variable % 2 == 0) {
        tmp = GameObject::BONUS_ATTACK_SPEED;
        bonus_name = Bonus::ATTACK_SPEED;
    } else {
        tmp = GameObject::BONUS_HEAL;
        bonus_name = Bonus::HEAL;
    }

    entity_id = world.create_bonus(
        tmp, Vector2f{pos.x, pos.y}, Vector2i{0, 0}, 0.04f, bonus_name);
    
    world.getRegistry().add_component<EntityIDComponent>(
        world.getRegistry().entity_from_index(entity_id), EntityIDComponent{entity_id});
    sending_msg.header.id = GameMessage::S2C_ENTITY_NEW;
    sending_msg << tmp;
    sending_msg << entity_id;
    sending_msg << Vector2f{pos.x, pos.y};
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
                velocity[index]->speed.x = move.x * defaultValues[GameObject::PLAYER].spd;
                velocity[index]->speed.y = move.y * defaultValues[GameObject::PLAYER].spd;
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

static std::map<std::string, Vector2f> shootMap = {{"assets/r-typesheet5.gif", Vector2f{50, 10}}};

void player_shot(World &world, ClientMessage msg, NetworkServer &server)
{
    registry &r = world.getRegistry();
    sparse_array<PositionComponent> &position = r.get_components<PositionComponent>();
    sparse_array<ClientIDComponent> &clients = r.get_components<ClientIDComponent>();
    sparse_array<DrawableComponent> &draw = r.get_components<DrawableComponent>();
    std::size_t index = 0;
    Message<GameMessage> sending_msg;
    size_t entity_id = 0;

    for (auto &i : clients) {
        if (i && i.has_value()) {
            if (i.value().id == msg.second) {
                Vector2f shootPos = shootMap[draw[index]->path];
                entity_id = world.create_laser(GameObject::LASER, GameTeam::PLAYER,
                    Vector2f{position[index]->pos.x + shootPos.x, position[index]->pos.y + shootPos.y},
                    Vector2i{defaultValues[GameObject::LASER].spd, 0}, 0.04f);
                std::cout << "Player[" << msg.second << "]: shot from Position{" << position[index]->pos.x << ", "
                          << position[index]->pos.y << "}" << std::endl;
                world.getRegistry().add_component<EntityIDComponent>(
                    world.getRegistry().entity_from_index(entity_id), EntityIDComponent{entity_id});
                sending_msg.header.id = GameMessage::S2C_ENTITY_NEW;
                sending_msg << GameObject::LASER;
                sending_msg << entity_id;
                sending_msg << Vector2f{position[index]->pos.x + shootPos.x, position[index]->pos.y + shootPos.y};
                server.SendToAll(sending_msg);
                sending_msg.header.id = GameMessage::S2C_MOVEMENT;
                sending_msg << entity_id;
                sending_msg << Vector2i{defaultValues[GameObject::LASER].spd, 0};
                server.SendToAll(sending_msg);
                break;
            }
        }
        index++;
    }
}
