/**
 * @file AISystem.cpp
 * @author Tanguy Bellicha (tanguy.bellicha@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-10-29
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "../Common/Message/Message.hpp"
#include "../Common/Message/MessageType.hpp"
#include "../ECS/Components/AllComponents.hpp"
#include "../ECS/World.hpp"
#include "game.hpp"

/**
 * @brief Goes to the left and follow the Y of player
 *
 * @param world The world
 * @param server The server
 * @param i The index of the enemy
 */
void update_enemy_focus(World &world, NetworkServer &server, size_t i)
{
    auto &clients = world.getRegistry().get_components<ClientIDComponent>();
    auto &velocity = world.getRegistry().get_components<VelocityComponent>();
    auto &entities = world.getRegistry().get_components<EntityIDComponent>();
    auto &positions = world.getRegistry().get_components<PositionComponent>();
    Message<GameMessage> sending_msg;
    Vector2i nearest_player_pos = {0, 0};
    bool default_player = false;

    for (size_t c = 0; c < clients.size(); ++c) {
        if (clients[c]) {
            if (!default_player) {
                nearest_player_pos.y = positions[c]->pos.y;
                default_player = true;
            }
            if (std::abs(nearest_player_pos.y - positions[i]->pos.y)
                >= std::abs(positions[i]->pos.y - positions[c]->pos.y)) {
                nearest_player_pos.y = positions[c]->pos.y;
                if (std::abs(positions[i]->pos.y - positions[c]->pos.y) <= defaultValues[GameObject::ENEMY_FOCUS].spd)
                    velocity[i]->speed.y = 0;
                else if (nearest_player_pos.y > positions[i]->pos.y) {
                    velocity[i]->speed.y = defaultValues[GameObject::ENEMY_FOCUS].spd;
                } else {
                    velocity[i]->speed.y = -defaultValues[GameObject::ENEMY_FOCUS].spd;
                }
                sending_msg.header.id = GameMessage::S2C_MOVEMENT;
                sending_msg << entities[i]->id;
                sending_msg << velocity[i]->speed;
                server.SendToAll(sending_msg);
                sending_msg = Message<GameMessage>();
            }
        }
    }
}

void update_enemy_sniper(World &world, NetworkServer &server, size_t i)
{
    auto &clients = world.getRegistry().get_components<ClientIDComponent>();
    auto &velocity = world.getRegistry().get_components<VelocityComponent>();
    auto &entities = world.getRegistry().get_components<EntityIDComponent>();
    auto &positions = world.getRegistry().get_components<PositionComponent>();
    Message<GameMessage> sending_msg;
    Vector2i nearest_player_pos = {0, 0};
    bool default_player = false;

    for (size_t c = 0; c < clients.size(); ++c) {
        if (clients[c]) {
            if (!default_player) {
                nearest_player_pos.y = positions[c]->pos.y;
                default_player = true;
            }
            if (std::abs(nearest_player_pos.y - positions[i]->pos.y)
                >= std::abs(positions[i]->pos.y - positions[c]->pos.y)) {
                nearest_player_pos.y = positions[c]->pos.y;
                if (std::abs(positions[i]->pos.y - positions[c]->pos.y) <= defaultValues[GameObject::ENEMY_SNIPER].spd)
                    velocity[i]->speed.y = 0;
                else if (nearest_player_pos.y > positions[i]->pos.y) {
                    velocity[i]->speed.y = defaultValues[GameObject::ENEMY_SNIPER].spd;
                } else {
                    velocity[i]->speed.y = -defaultValues[GameObject::ENEMY_SNIPER].spd;
                }
                if (positions[i]->pos.x <= 1820)
                    velocity[i]->speed.x = 0;
                sending_msg.header.id = GameMessage::S2C_MOVEMENT;
                sending_msg << entities[i]->id;
                sending_msg << velocity[i]->speed;
                server.SendToAll(sending_msg);
                sending_msg = Message<GameMessage>();
            }
        }
    }
}

/**
 * @brief Don't do anything for the kamikaze, it only goes to the left
 *
 * @param world The world
 * @param server The server
 * @param i The index of the enemy
 */
void update_enemy_kamikaze(World &world, NetworkServer &server, size_t i)
{
    (void)world;
    (void)server;
    (void)i;
}

/**
 * @brief Call a function by a GameObject type
 */
static std::map<GameObject, std::function<void(World &, NetworkServer &, size_t)>> mapFunc = {
    {GameObject::ENEMY_FOCUS, update_enemy_focus}, {GameObject::ENEMY_KAMIKAZE, update_enemy_kamikaze},
    {GameObject::ENEMY_SNIPER, update_enemy_sniper}, {GameObject::BOSS_1, update_enemy_focus}};

/**
 * @brief
 *
 * @param world The world
 * @param server The server
 * @return int
 */
int ia_system(World &world, NetworkServer &server)
{
    auto &teams = world.getRegistry().get_components<GameTeamComponent>();
    auto &objects = world.getRegistry().get_components<GameObjectComponent>();

    for (size_t i = 0; i < teams.size(); ++i)
        if (teams[i] && teams[i]->team == GameTeam::ENEMY)
            mapFunc[objects[i]->type](world, server, i);
    return 0;
}
