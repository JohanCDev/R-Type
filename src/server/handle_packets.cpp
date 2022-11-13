/**
 * @file handle_packets.cpp
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
    (void)msg;
    (void)server;
    if (world.state != GameState::Lobby)
        return;
}

void bonus_creation(World &world, NetworkServer &server, Vector2f pos)
{
    size_t entity_id = 0;
    Message<GameMessage> sending_msg;
    GameObject tmp;
    std::srand(std::time(nullptr));
    int random_variable = std::rand();
    Bonus bonus_name;

    if (random_variable % 5 == 0) {
        tmp = GameObject::BONUS_ATTACK;
        bonus_name = Bonus::ATTACK;
    } else if (random_variable % 4 == 0) {
        tmp = GameObject::BONUS_ATTACK_SPEED;
        bonus_name = Bonus::ATTACK_SPEED;
    } else if (random_variable % 3 == 0) {
        tmp = GameObject::BONUS_HEAL;
        bonus_name = Bonus::HEAL;
    } else if (random_variable % 2 == 0) {
        tmp = GameObject::BONUS_SPEED;
        bonus_name = Bonus::SPEED;
    } else {
        tmp = GameObject::BONUS_DOUBLE;
        bonus_name = Bonus::DOUBLE;
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
            sending_msg = Message<GameMessage>();
            server.clients.left.erase(msg.second);
            world.player_ships.erase(msg.second);
            break;
        }
        index++;
    }
    std::size_t nbr = server.clients.size();

    sending_msg.header.id = GameMessage::S2C_PLAYERS_IN_LOBBY;
    sending_msg << nbr;
    server.SendToAll(sending_msg);
}

void player_moved(World &world, ClientMessage msg, NetworkServer &server)
{
    Vector2i move{0, 0};
    registry &r = world.getRegistry();
    sparse_array<VelocityComponent> &velocity = r.get_components<VelocityComponent>();
    sparse_array<ClientIDComponent> &clients = r.get_components<ClientIDComponent>();
    sparse_array<EntityIDComponent> &entities = r.get_components<EntityIDComponent>();
    sparse_array<SpeedComponent> &speed = r.get_components<SpeedComponent>();
    std::size_t index = 0;
    Message<GameMessage> sending_msg;

    msg.first >> move;
    for (auto &i : clients) {
        if (i && i.has_value()) {
            if (i.value().id == msg.second) {
                velocity[index]->speed.x = move.x * speed[index]->speed;
                velocity[index]->speed.y = move.y * speed[index]->speed;
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

static std::map<std::string, Vector2f> shootMap = {{"assets/r-typesheet5.gif", Vector2f{50, 10}},
    {"assets/SpaceShip/ship_armored_spritesheet.png", Vector2f{130, 55}},
    {"assets/SpaceShip/ship_damage_spritesheet.png", Vector2f{110, 64}},
    {"assets/SpaceShip/ship_engineer_spritesheet.png", Vector2f{128, 62}},
    {"assets/SpaceShip/ship_sniper_spritesheet.png", Vector2f{116, 60}}};

void player_shot(World &world, ClientMessage msg, NetworkServer &server)
{
    registry &r = world.getRegistry();
    sparse_array<PositionComponent> &position = r.get_components<PositionComponent>();
    sparse_array<ClientIDComponent> &clients = r.get_components<ClientIDComponent>();
    sparse_array<DrawableComponent> &draw = r.get_components<DrawableComponent>();
    sparse_array<DoubleLaserComponent> &laser = r.get_components<DoubleLaserComponent>();
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
                world.getRegistry().add_component<EntityIDComponent>(
                    world.getRegistry().entity_from_index(entity_id), EntityIDComponent{entity_id});
                sending_msg.header.id = GameMessage::S2C_ENTITY_NEW;
                sending_msg << GameObject::LASER;
                sending_msg << entity_id;
                sending_msg << Vector2f{position[index]->pos.x + shootPos.x, position[index]->pos.y + shootPos.y};
                server.SendToAll(sending_msg);
                sending_msg = Message<GameMessage>();
                sending_msg.header.id = GameMessage::S2C_MOVEMENT;
                sending_msg << entity_id;
                sending_msg << Vector2i{defaultValues[GameObject::LASER].spd, 0};
                server.SendToAll(sending_msg);
                if (laser[index]->_double == true) {
                    Vector2f shootPos2 = shootMap[draw[index]->path];
                    entity_id = world.create_laser(GameObject::LASER, GameTeam::PLAYER,
                        Vector2f{position[index]->pos.x + shootPos2.x, position[index]->pos.y + shootPos2.y - 30},
                        Vector2i{defaultValues[GameObject::LASER].spd, 0}, 0.04f);
                    world.getRegistry().add_component<EntityIDComponent>(
                        world.getRegistry().entity_from_index(entity_id), EntityIDComponent{entity_id});
                    sending_msg.header.id = GameMessage::S2C_ENTITY_NEW;
                    sending_msg << GameObject::LASER;
                    sending_msg << entity_id;
                    sending_msg << Vector2f{position[index]->pos.x + shootPos2.x, position[index]->pos.y + shootPos2.y - 30};
                    server.SendToAll(sending_msg);
                    sending_msg.header.id = GameMessage::S2C_MOVEMENT;
                    sending_msg << entity_id;
                    sending_msg << Vector2i{defaultValues[GameObject::LASER].spd, 0};
                    server.SendToAll(sending_msg);
                }
                break;
            }
        }
        index++;
    }
}

void start_game(World &world, ClientMessage msg, NetworkServer &server)
{
    Message<GameMessage> sending_msg;
    size_t entity_id = 0;

    sending_msg.header.id = GameMessage::S2C_START_GAME;
    sending_msg << "start";
    server.SendToAll(sending_msg);
    for (std::map<std::size_t, GameObject>::iterator it = world.player_ships.begin(); it != world.player_ships.end();
         ++it) {
        entity_id = world.create_player(it->second,
            Vector2f{defaultValues[it->second].pos.x, defaultValues[it->second].pos.y}, Vector2i{0, 0}, 0.04f);
        world.getRegistry().add_component<ClientIDComponent>(
            world.getRegistry().entity_from_index(entity_id), ClientIDComponent{it->first});
        world.getRegistry().add_component<EntityIDComponent>(
            world.getRegistry().entity_from_index(entity_id), EntityIDComponent{entity_id});
        sending_msg.header.id = GameMessage::S2C_ENTITY_NEW;
        sending_msg << it->second;
        sending_msg << entity_id;
        sending_msg << Vector2f{defaultValues[it->second].pos.x, defaultValues[it->second].pos.y};
        server.SendToAll(sending_msg);
    }
    world.state = GameState::Playing;
}

void select_ship(World &world, ClientMessage msg, NetworkServer &server)
{
    (void)server;
    GameObject ship;

    msg.first >> ship;
    world.player_ships[msg.second] = ship;
}

void spend_point(World &world, ClientMessage msg, NetworkServer &server)
{
    auto &levels = world.getRegistry().get_components<LevelComponent>();
    auto &teams = world.getRegistry().get_components<GameTeamComponent>();
    auto &clients = world.getRegistry().get_components<ClientIDComponent>();
    GameStat stat;

    msg.first >> stat;

    std::size_t index = 0;

    for (auto &client : clients) {
        if (!(client && client.has_value() && client->id == msg.second)) {
            index++;
        }
        auto &level = levels[index];
        if (level && level.has_value()) {
            if (level->spent_points >= level->level) {
                return;
            }
            auto &team = teams[index];
            if (team && team.has_value() && team->team == GameTeam::PLAYER) {
                stat_up(world, stat, index);
                send_stats_to_players(world, server, index);
                level->spent_points++;
            }
        }
        break;
    }
}
