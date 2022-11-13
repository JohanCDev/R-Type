/**
 * @file new_entity.cpp
 * @author Tanguy Bellicha (tanguy.bellicha@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-11-02
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "client.hpp"
#include "proto.hpp"

void new_player(World &world, size_t srv_entity_id, Vector2f pos)
{
    size_t new_entity_id = 0;
    PositionComponent position(pos);

    new_entity_id = world.create_player(GameObject::PLAYER, position.pos, Vector2i{0, 0}, 0.04f);
    world.getRegistry().add_component<EntityIDComponent>(
        world.getRegistry().entity_from_index(new_entity_id), EntityIDComponent{srv_entity_id});
    std::cout << "Player[" << srv_entity_id << "]: joined the game at (" << pos.x << ", " << pos.y << ")" << std::endl;
}

void new_armored_player(World &world, size_t srv_entity_id, Vector2f pos)
{
    size_t new_entity_id;
    PositionComponent position(pos);

    new_entity_id = world.create_player(GameObject::SHIP_ARMORED, position.pos, Vector2i{0, 0}, 0.04f);
    world.getRegistry().add_component<EntityIDComponent>(
        world.getRegistry().entity_from_index(new_entity_id), EntityIDComponent{srv_entity_id});
    std::cout << "Player[" << srv_entity_id << "]: joined the game at (" << pos.x << ", " << pos.y << ")" << std::endl;
}

void new_damage_player(World &world, size_t srv_entity_id, Vector2f pos)
{
    size_t new_entity_id;
    PositionComponent position(pos);

    new_entity_id = world.create_player(GameObject::SHIP_DAMAGE, position.pos, Vector2i{0, 0}, 0.04f);
    world.getRegistry().add_component<EntityIDComponent>(
        world.getRegistry().entity_from_index(new_entity_id), EntityIDComponent{srv_entity_id});
    std::cout << "Player[" << srv_entity_id << "]: joined the game at (" << pos.x << ", " << pos.y << ")" << std::endl;
}

void new_engineer_player(World &world, size_t srv_entity_id, Vector2f pos)
{
    size_t new_entity_id;
    PositionComponent position(pos);

    new_entity_id = world.create_player(GameObject::SHIP_ENGINEER, position.pos, Vector2i{0, 0}, 0.04f);
    world.getRegistry().add_component<EntityIDComponent>(
        world.getRegistry().entity_from_index(new_entity_id), EntityIDComponent{srv_entity_id});
    std::cout << "Player[" << srv_entity_id << "]: joined the game at (" << pos.x << ", " << pos.y << ")" << std::endl;
}

void new_sniper_player(World &world, size_t srv_entity_id, Vector2f pos)
{
    size_t new_entity_id;
    PositionComponent position(pos);

    new_entity_id = world.create_player(GameObject::SHIP_SNIPER, position.pos, Vector2i{0, 0}, 0.04f);
    world.getRegistry().add_component<EntityIDComponent>(
        world.getRegistry().entity_from_index(new_entity_id), EntityIDComponent{srv_entity_id});
    std::cout << "Player[" << srv_entity_id << "]: joined the game at (" << pos.x << ", " << pos.y << ")" << std::endl;
}

void new_enemy_focus(World &world, size_t srv_entity_id, Vector2f pos)
{
    size_t new_entity_id = 0;
    PositionComponent position(pos);

    new_entity_id = world.create_enemy(GameObject::ENEMY_FOCUS, position.pos, Vector2i{0, 0}, 1, 0.04f);
    world.getRegistry().add_component<EntityIDComponent>(
        world.getRegistry().entity_from_index(new_entity_id), EntityIDComponent{srv_entity_id});
    std::cout << "Enemy[" << srv_entity_id << "]: spawned at (" << pos.x << ", " << pos.y << ")" << std::endl;
}

void new_enemy_sniper(World &world, size_t srv_entity_id, Vector2f pos)
{
    size_t new_entity_id = 0;
    PositionComponent position(pos);

    new_entity_id = world.create_enemy(GameObject::ENEMY_SNIPER, position.pos, Vector2i{0, 0}, 1, 0.04f);
    world.getRegistry().add_component<EntityIDComponent>(
        world.getRegistry().entity_from_index(new_entity_id), EntityIDComponent{srv_entity_id});
    std::cout << "Enemy[" << srv_entity_id << "]: spawned at (" << pos.x << ", " << pos.y << ")" << std::endl;
}

void new_enemy_kamikaze(World &world, size_t srv_entity_id, Vector2f pos)
{
    size_t new_entity_id = 0;
    PositionComponent position(pos);

    new_entity_id = world.create_enemy(GameObject::ENEMY_KAMIKAZE, position.pos, Vector2i{0, 0}, 1, 0.04f);
    world.getRegistry().add_component<EntityIDComponent>(
        world.getRegistry().entity_from_index(new_entity_id), EntityIDComponent{srv_entity_id});
    std::cout << "Enemy[" << srv_entity_id << "]: spawned at (" << pos.x << ", " << pos.y << ")" << std::endl;
}

void new_boss1(World &world, size_t srv_entity_id, Vector2f pos)
{
    size_t new_entity_id = 0;
    PositionComponent position(pos);

    new_entity_id = world.create_enemy(GameObject::BOSS_1, position.pos, Vector2i{0, 0}, 1, 0.04f);
    world.getRegistry().add_component<EntityIDComponent>(
        world.getRegistry().entity_from_index(new_entity_id), EntityIDComponent{srv_entity_id});
    std::cout << "Boss1[" << srv_entity_id << "]: spawned at (" << pos.x << ", " << pos.y << ")" << std::endl;
}

void new_laser(World &world, size_t srv_entity_id, Vector2f pos)
{
    size_t new_entity_id = 0;
    PositionComponent position(pos);

    new_entity_id = world.create_laser(
        GameObject::LASER, GameTeam::PLAYER, position.pos, Vector2i{0, 0}, 0.04f);
    world.getRegistry().add_component<EntityIDComponent>(
        world.getRegistry().entity_from_index(new_entity_id), EntityIDComponent{srv_entity_id});
    std::cout << "Laser[" << srv_entity_id << "]: spawned at (" << pos.x << ", " << pos.y << ")" << std::endl;
}

void new_laser_enemy(World &world, size_t srv_entity_id, Vector2f pos)
{
    size_t new_entity_id = 0;
    PositionComponent position(pos);

    new_entity_id = world.create_laser_enemy(
        GameObject::LASER_ENEMY, GameTeam::ENEMY, position.pos, Vector2i{0, 0}, 0.04f);
    world.getRegistry().add_component<EntityIDComponent>(
        world.getRegistry().entity_from_index(new_entity_id), EntityIDComponent{srv_entity_id});
    std::cout << "LaserEnemy[" << srv_entity_id << "]: spawned at (" << pos.x << ", " << pos.y << ")" << std::endl;
}
