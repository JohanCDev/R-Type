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
 * @param i The index of the entity
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

/**
 * @brief Stay on the right of the screen and move vertically
 *
 * @param world The world
 * @param server The server
 * @param i The index of the entity
 */
void update_enemy_sniper(World &world, NetworkServer &server, size_t i)
{
    auto &velocity = world.getRegistry().get_components<VelocityComponent>();
    auto &entities = world.getRegistry().get_components<EntityIDComponent>();
    auto &positions = world.getRegistry().get_components<PositionComponent>();
    Message<GameMessage> sending_msg;
    int random_dir = rand() % 2;
    int random_shoot = rand() % 32;
    size_t entity_id = 0;

    if (positions[i]->pos.x < 1820 && velocity[i]->speed.x != 0) {
        velocity[i]->speed.x = 0;
        if (random_dir == 1)
            velocity[i]->speed.y = defaultValues[GameObject::ENEMY_SNIPER].spd;
        else
            velocity[i]->speed.y = -defaultValues[GameObject::ENEMY_SNIPER].spd;
        sending_msg.header.id = GameMessage::S2C_MOVEMENT;
        sending_msg << entities[i]->id;
        sending_msg << velocity[i]->speed;
        server.SendToAll(sending_msg);
        sending_msg = Message<GameMessage>();
    } else if (velocity[i]->speed.x == 0) {
        if (positions[i]->pos.y < 100 && velocity[i]->speed.y == -defaultValues[GameObject::ENEMY_SNIPER].spd) {
            velocity[i]->speed.y = defaultValues[GameObject::ENEMY_SNIPER].spd;
            sending_msg.header.id = GameMessage::S2C_MOVEMENT;
            sending_msg << entities[i]->id;
            sending_msg << velocity[i]->speed;
            server.SendToAll(sending_msg);
            sending_msg = Message<GameMessage>();
        } else if (positions[i]->pos.y > 980 && velocity[i]->speed.y == defaultValues[GameObject::ENEMY_SNIPER].spd) {
            velocity[i]->speed.y = -defaultValues[GameObject::ENEMY_SNIPER].spd;
            sending_msg.header.id = GameMessage::S2C_MOVEMENT;
            sending_msg << entities[i]->id;
            sending_msg << velocity[i]->speed;
            server.SendToAll(sending_msg);
            sending_msg = Message<GameMessage>();
        }
        if (random_shoot < 2) {
            entity_id = world.create_laser_enemy(GameObject::LASER_ENEMY, GameTeam::ENEMY, positions[i]->pos,
                Vector2i{defaultValues[GameObject::LASER_ENEMY].spd, 0}, 0.04f);
            world.getRegistry().add_component<EntityIDComponent>(
                world.getRegistry().entity_from_index(entity_id), EntityIDComponent{entity_id});
            sending_msg.header.id = GameMessage::S2C_ENTITY_NEW;
            sending_msg << GameObject::LASER_ENEMY;
            sending_msg << entity_id;
            sending_msg << positions[i]->pos;
            server.SendToAll(sending_msg);
            sending_msg = Message<GameMessage>();
            sending_msg.header.id = GameMessage::S2C_MOVEMENT;
            sending_msg << entity_id;
            sending_msg << Vector2i{defaultValues[GameObject::LASER_ENEMY].spd, 0};
            server.SendToAll(sending_msg);
            sending_msg = Message<GameMessage>();
        }
    }
}

/**
 * @brief Don't do anything for the kamikaze, it only goes to the left
 *
 * @param world The world
 * @param server The server
 * @param i The index of the entity
 */
void update_enemy_kamikaze(World &world, NetworkServer &server, size_t i)
{
    (void)world;
    (void)server;
    (void)i;
}

/**
 * @brief Stay on the right of the screen and follow the nearest player vertically
 *
 * @param world The world
 * @param server The server
 * @param i The index of the entity
 */
void update_boss_1(World &world, NetworkServer &server, size_t i)
{
    auto &clients = world.getRegistry().get_components<ClientIDComponent>();
    auto &velocity = world.getRegistry().get_components<VelocityComponent>();
    auto &entities = world.getRegistry().get_components<EntityIDComponent>();
    auto &positions = world.getRegistry().get_components<PositionComponent>();
    Message<GameMessage> sending_msg;
    Vector2i nearest_player_pos = {0, 0};
    bool default_player = false;
    size_t random_shoot = rand() % 10;
    size_t entity_id = 0;

    for (size_t c = 0; c < clients.size(); ++c) {
        if (clients[c]) {
            if (!default_player) {
                nearest_player_pos.y = positions[c]->pos.y;
                default_player = true;
            }
            if (std::abs(nearest_player_pos.y - positions[i]->pos.y)
                >= std::abs(positions[i]->pos.y - positions[c]->pos.y)) {
                nearest_player_pos.y = positions[c]->pos.y;
                if (std::abs(positions[i]->pos.y - positions[c]->pos.y) <= defaultValues[GameObject::BOSS_1].spd)
                    velocity[i]->speed.y = 0;
                else if (nearest_player_pos.y > positions[i]->pos.y)
                    velocity[i]->speed.y = defaultValues[GameObject::BOSS_1].spd;
                else
                    velocity[i]->speed.y = -defaultValues[GameObject::BOSS_1].spd;
                if (positions[i]->pos.x <= 1420)
                    velocity[i]->speed.x = 0;
                if (random_shoot == 2) {
                    for (int s = 0; s < 3; s++) {
                        Vector2f shoot_pos = {positions[i]->pos.x, positions[i]->pos.y + s * 50};
                        entity_id = world.create_laser_enemy(GameObject::LASER_ENEMY, GameTeam::ENEMY, shoot_pos,
                            Vector2i{defaultValues[GameObject::LASER_ENEMY].spd, 0}, 0.04f);
                        world.getRegistry().add_component<EntityIDComponent>(
                            world.getRegistry().entity_from_index(entity_id), EntityIDComponent{entity_id});
                        sending_msg.header.id = GameMessage::S2C_ENTITY_NEW;
                        sending_msg << GameObject::LASER_ENEMY;
                        sending_msg << entity_id;
                        sending_msg << shoot_pos;
                        server.SendToAll(sending_msg);
                        sending_msg = Message<GameMessage>();
                    }
                }
                sending_msg.header.id = GameMessage::S2C_MOVEMENT;
                sending_msg << entities[i]->id;
                sending_msg << velocity[i]->speed;
                server.SendToAll(sending_msg);
                sending_msg = Message<GameMessage>();
                break;
            }
        }
    }
}

/**
 * @brief Call a function by a GameObject type
 */
static std::map<GameObject, std::function<void(World &, NetworkServer &, size_t)>> mapFunc = {
    {GameObject::ENEMY_FOCUS, update_enemy_focus}, {GameObject::ENEMY_KAMIKAZE, update_enemy_kamikaze},
    {GameObject::ENEMY_SNIPER, update_enemy_sniper}, {GameObject::BOSS_1, update_boss_1}};

int ia_system(World &world, NetworkServer &server)
{
    auto &teams = world.getRegistry().get_components<GameTeamComponent>();
    auto &objects = world.getRegistry().get_components<GameObjectComponent>();

    for (size_t i = 0; i < teams.size(); ++i)
        if (teams[i] && teams[i]->team == GameTeam::ENEMY && objects[i] && objects[i]->type != GameObject::LASER_ENEMY)
            mapFunc[objects[i]->type](world, server, i);
    return 0;
}
