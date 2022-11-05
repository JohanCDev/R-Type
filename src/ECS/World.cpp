/**
 * @file World.cpp
 * @author Cédric Corge (cedric.corge@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-10-17
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "World.hpp"
#include <iostream>

World::World(sf::VideoMode mode, std::string name)
    : _r(), _manager(), _window(mode, name), _clock(), _player_direction({0, 0})
{
}

World::World() : _r(), _clock()
{
}

World::~World()
{
}

void World::register_all_component()
{
    this->_r.register_components<ClientIDComponent>();
    this->_r.register_components<CollideComponent>();
    this->_r.register_components<ControllableComponent>();
    this->_r.register_components<DestroyableComponent>();
    this->_r.register_components<DrawableComponent>();
    this->_r.register_components<EntityIDComponent>();
    this->_r.register_components<GameTeamComponent>();
    this->_r.register_components<HealthComponent>();
    this->_r.register_components<ImmobileComponent>();
    this->_r.register_components<PositionComponent>();
    this->_r.register_components<VelocityComponent>();
    this->_r.register_components<WeaponComponent>();
}

void World::register_all_system()
{
    // this->_r.register_systems(&velocity_system);
    // this->_r.register_systems(&shooting_system);
}

void World::register_all_assets()
{
    this->_manager.register_texture("assets/r-typesheet1.gif");
    this->_manager.register_texture("assets/r-typesheet5.gif");
    this->_manager.register_texture("assets/r-typesheet39.gif");
    this->_manager.register_texture("assets/Boss/boss1.png");
    this->_manager.register_texture("assets/Power-up/boost_attack.png");
}

sf::Clock &World::getClock()
{
    return (this->_clock);
}

sf::RenderWindow &World::getWindow()
{
    return (this->_window);
}

ResourcesManager &World::getResourcesManager()
{
    return (this->_manager);
}

registry &World::getRegistry()
{
    return (this->_r);
}

Vector2i &World::getDirection()
{
    return (this->_player_direction);
}

void World::setDirection(Vector2i direction)
{
    this->_player_direction = direction;
}

size_t World::create_laser(GameObject object, GameTeam team, Vector2f pos, Vector2i speed, float refresh_time)
{
    Entity ent = this->_r.spawn_entity();

    DrawableComponent drawCompo = this->_drawMap[object];
    this->_r.add_component<DrawableComponent>(ent, DrawableComponent(drawCompo.path, drawCompo.rect, drawCompo.scale));
    this->_r.add_component<WeaponComponent>(ent, WeaponComponent("laser", Vector2i{40, 15}, 200));
    this->_r.add_component<VelocityComponent>(
        ent, VelocityComponent(speed, refresh_time, this->_clock.getElapsedTime().asSeconds()));
    this->_r.add_component<PositionComponent>(ent, PositionComponent(pos));
    this->_r.add_component<HealthComponent>(ent, HealthComponent(1));
    this->_r.add_component<GameTeamComponent>(ent, GameTeamComponent(team));
    return (ent.id);
}

size_t World::create_player(GameObject object, Vector2f pos, Vector2i speed, float refresh_time)
{
    Entity ent = this->_r.spawn_entity();

    DrawableComponent drawCompo = this->_drawMap[object];
    this->_r.add_component<DrawableComponent>(ent, DrawableComponent(drawCompo.path, drawCompo.rect, drawCompo.scale));
    this->_r.add_component<PositionComponent>(ent, PositionComponent(pos));
    this->_r.add_component<ImmobileComponent>(ent, ImmobileComponent(Vector2b(true, true)));
    this->_r.add_component<DestroyableComponent>(ent, DestroyableComponent(true));
    this->_r.add_component<HealthComponent>(ent, HealthComponent(100));
    this->_r.add_component<VelocityComponent>(
        ent, VelocityComponent(speed, refresh_time, this->_clock.getElapsedTime().asSeconds()));
    this->_r.add_component<GameTeamComponent>(ent, GameTeamComponent(GameTeam::PLAYER));
    this->_r.add_component<ControllableComponent>(ent,
        ControllableComponent(
            KeyboardInput::Z, KeyboardInput::S, KeyboardInput::D, KeyboardInput::Q, MouseInput::Left_click));

    return (ent.id);
}

size_t World::create_enemy(GameObject object, Vector2f pos, Vector2i speed, size_t health, float refresh_time)
{
    Entity ent = this->_r.spawn_entity();

    DrawableComponent drawCompo = this->_drawMap[object];
    this->_r.add_component<DrawableComponent>(ent, DrawableComponent(drawCompo.path, drawCompo.rect, drawCompo.scale));
    this->_r.add_component<PositionComponent>(ent, PositionComponent(pos));
    this->_r.add_component<ImmobileComponent>(ent, ImmobileComponent(Vector2b(false, false)));
    this->_r.add_component<CollideComponent>(ent, CollideComponent());
    this->_r.add_component<WeaponComponent>(ent, WeaponComponent("meteor", Vector2i{35, 1}, 0));
    this->_r.add_component<DestroyableComponent>(ent, DestroyableComponent(true));
    this->_r.add_component<HealthComponent>(ent, HealthComponent(health));
    this->_r.add_component<VelocityComponent>(
        ent, VelocityComponent(speed, refresh_time, this->_clock.getElapsedTime().asSeconds()));
    this->_r.add_component<GameTeamComponent>(ent, GameTeamComponent(GameTeam::ENEMY));

    return (ent.id);
}

size_t World::create_bonus(GameObject object, Vector2f pos, Vector2i speed, float refresh_time)
{
    Entity ent = this->_r.spawn_entity();

    DrawableComponent drawCompo = this->_drawMap[object];
    this->_r.add_component<DrawableComponent>(ent, DrawableComponent(drawCompo.path, drawCompo.rect, drawCompo.scale));
    this->_r.add_component<PositionComponent>(ent, PositionComponent(pos));
    this->_r.add_component<ImmobileComponent>(ent, ImmobileComponent(Vector2b(false, false)));
    this->_r.add_component<DestroyableComponent>(ent, DestroyableComponent(true));
    this->_r.add_component<HealthComponent>(ent, HealthComponent(100));
    this->_r.add_component<VelocityComponent>(
        ent, VelocityComponent(speed, refresh_time, this->_clock.getElapsedTime().asSeconds()));
    this->_r.add_component<GameTeamComponent>(ent, GameTeamComponent(GameTeam::ENEMY));
    // this->_r.add_component<ControllableComponent>(ent,
    //     ControllableComponent(
    //         KeyboardInput::Z, KeyboardInput::S, KeyboardInput::D, KeyboardInput::Q, MouseInput::Left_click));

    return (ent.id);
}

void World::register_all_drawable_object()
{
    this->_drawMap.emplace(GameObject::LASER, DrawableComponent("assets/r-typesheet1.gif", Vector4i(104, 171, 80, 14)));
    this->_drawMap.emplace(
        GameObject::PLAYER, DrawableComponent("assets/r-typesheet5.gif", Vector4i{375, 6, 21, 24}, Vector2f{2.0, 2.0}));
    this->_drawMap.emplace(GameObject::ENEMY_FOCUS,
        DrawableComponent("assets/r-typesheet39.gif", Vector4i{34, 2, 64, 64}, Vector2f{1.0, 1.0}));
    this->_drawMap.emplace(GameObject::ENEMY_SNIPER,
        DrawableComponent("assets/r-typesheet39.gif", Vector4i{34, 2, 64, 64}, Vector2f{1.0, 1.0}));
    this->_drawMap.emplace(GameObject::ENEMY_ODD,
        DrawableComponent("assets/r-typesheet39.gif", Vector4i{34, 2, 64, 64}, Vector2f{1.0, 1.0}));
    this->_drawMap.emplace(
        GameObject::BOSS_1, DrawableComponent("assets/Boss/boss1.png", Vector4i{0, 0, 245, 245}, Vector2f{1.0, 1.0}));
    this->_drawMap.emplace(
        GameObject::BONUS, DrawableComponent("assets/Power-up/boost_attack.png", Vector4i{0, 0, 512, 512}, Vector2f{0.3, 0.3}));
}
