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

World::World(sf::VideoMode mode, std::string name) : _r(), _manager(), _window(mode, name), _clock()
{
}

World::World(void) : _r(), _clock()
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
    this->_r.register_components<HealthComponent>();
    this->_r.register_components<ImmobileComponent>();
    this->_r.register_components<PositionComponent>();
    this->_r.register_components<VelocityComponent>();
    this->_r.register_components<WeaponComponent>();
}

void World::register_all_system()
{
    this->_r.register_systems(&velocity_system);
    this->_r.register_systems(&shooting_system);
}

void World::register_all_assets()
{
    this->_manager.register_texture("assets/r-typesheet1.gif");
    this->_manager.register_texture("assets/r-typesheet5.gif");
    this->_manager.register_texture("assets/r-typesheet39.gif");
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

void World::create_laser(Vector2i pos, Vector2i speed, float refresh_time, float elapsed_time)
{
    Entity ent = this->_r.spawn_entity();
    this->_r.add_component<DrawableComponent>(
        ent, DrawableComponent("assets/r-typesheet1.gif", Vector4i(104, 171, 80, 14)));
    this->_r.add_component<WeaponComponent>(ent, WeaponComponent("laser", Vector2i{5, 15}, 0.2));
    this->_r.add_component<VelocityComponent>(ent, VelocityComponent(speed, refresh_time, elapsed_time));
    this->_r.add_component<PositionComponent>(ent, PositionComponent(pos));
}

size_t World::create_player(std::string texture_path, Vector4i texture_rec, Vector2f scale, Vector2i pos, int hp,
    Vector2i speed, float refresh_time, KeyboardInput up, KeyboardInput down, KeyboardInput right, KeyboardInput left,
    MouseInput shoot)
{
    Entity ent = this->_r.spawn_entity();
    this->_r.add_component<DrawableComponent>(ent, DrawableComponent(texture_path, texture_rec, scale));
    this->_r.add_component<PositionComponent>(ent, PositionComponent(pos));
    this->_r.add_component<ImmobileComponent>(ent, ImmobileComponent(Vector2b(true, true)));
    this->_r.add_component<CollideComponent>(ent, CollideComponent());
    this->_r.add_component<HealthComponent>(ent, (HealthComponent(hp)));
    this->_r.add_component<VelocityComponent>(ent, VelocityComponent(speed, refresh_time));
    this->_r.add_component<ControllableComponent>(ent, ControllableComponent(up, down, right, left, shoot));
    return (ent.id);
}

size_t World::create_enemy(std::string texture_path, Vector4i texture_rec, Vector2f scale, Vector2i pos, Vector2i speed,
    float refresh_time, float elapsed_time)
{
    Entity ent = this->_r.spawn_entity();
    this->_r.add_component<DrawableComponent>(ent, DrawableComponent(texture_path, texture_rec, scale));
    this->_r.add_component<PositionComponent>(ent, PositionComponent(pos));
    this->_r.add_component<ImmobileComponent>(ent, ImmobileComponent(Vector2b(false, false)));
    this->_r.add_component<CollideComponent>(ent, CollideComponent());
    this->_r.add_component<WeaponComponent>(ent, WeaponComponent("meteor", Vector2i{1, 1}, 0));
    this->_r.add_component<DestroyableComponent>(ent, DestroyableComponent(true));
    this->_r.add_component<VelocityComponent>(ent, VelocityComponent(speed, refresh_time, elapsed_time));
    return (ent.id);
}