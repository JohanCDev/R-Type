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
    (void)world;
    (void)server;
    (void)i;
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
 * @brief Give a direction by an index
 */
static std::map<size_t, Vector2i> next_dir = {{1, {0, -1}}, {2, {1, 0}}, {3, {0, 1}}, {4, {-1, 0}}};

/**
 * @brief Random direction for the enemy, can't go outside top_bot and left_right borders
 *
 * @param world The world
 * @param server The server
 * @param i The index of the enemy
 */
void update_enemy_odd(World &world, NetworkServer &server, size_t i)
{
    size_t random_spawn = rand() % 1000;
    size_t random_dir = rand() % 1000;
    Vector2i top_bot = {50, 1030};
    Vector2i left_right = {0, 1820};
    Vector2i next_pos = {0, 0};
    Message<GameMessage> sending_msg;
    auto &positions = world.getRegistry().get_components<PositionComponent>();
    auto &velocity = world.getRegistry().get_components<VelocityComponent>();
    auto &entities = world.getRegistry().get_components<EntityIDComponent>();

    random_dir = rand() % 4 + 1;
    if (positions[i]->pos.x < left_right.y) {
        next_pos.x = positions[i]->pos.x + next_dir[random_dir].x * defaultValues[GameObject::ENEMY_ODD].spd;
        next_pos.y = positions[i]->pos.y + next_dir[random_dir].y * defaultValues[GameObject::ENEMY_ODD].spd;
        if (next_pos.y <= top_bot.x || next_pos.y >= top_bot.y || next_pos.x >= left_right.y
            || next_pos.x <= left_right.x) {
            while (next_pos.y <= top_bot.x || next_pos.y >= top_bot.y || next_pos.x >= left_right.y
                || next_pos.x <= left_right.x) {
                random_dir = rand() % 4 + 1;
                next_pos.x = positions[i]->pos.x + next_dir[random_dir].x * defaultValues[GameObject::ENEMY_ODD].spd;
                next_pos.y = positions[i]->pos.y + next_dir[random_dir].y * defaultValues[GameObject::ENEMY_ODD].spd;
            }
            velocity[i]->speed.x = defaultValues[GameObject::ENEMY_ODD].spd * next_dir[random_dir].x;
            velocity[i]->speed.y = defaultValues[GameObject::ENEMY_ODD].spd * next_dir[random_dir].y;
            sending_msg.header.id = GameMessage::S2C_MOVEMENT;
            sending_msg << entities[i]->id;
            sending_msg << velocity[i]->speed;
            server.SendToAll(sending_msg);
            return;
        }
        if (random_spawn < 10) {
            velocity[i]->speed.x = defaultValues[GameObject::ENEMY_ODD].spd * next_dir[random_dir].x;
            velocity[i]->speed.y = defaultValues[GameObject::ENEMY_ODD].spd * next_dir[random_dir].y;
            sending_msg.header.id = GameMessage::S2C_MOVEMENT;
            sending_msg << entities[i]->id;
            sending_msg << velocity[i]->speed;
            server.SendToAll(sending_msg);
        }
    }
}

/**
 * @brief Call a function by a GameObject type
 */
static std::map<GameObject, std::function<void(World &, NetworkServer &, size_t)>> mapFunc = {
    {GameObject::ENEMY_FOCUS, update_enemy_focus}, {GameObject::ENEMY_KAMIKAZE, update_enemy_kamikaze},
    {GameObject::ENEMY_ODD, update_enemy_odd}, {GameObject::ENEMY_SNIPER, update_enemy_sniper},
    {GameObject::BOSS_1, update_enemy_focus}};

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
