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

World::World(sf::VideoMode mode, std::string name): _r(), _manager(), _window(mode, name), _clock()
{
}

World::~World()
{
}

void World::register_all_component()
{
    this->_r.register_components<ControllableComponent>();
    this->_r.register_components<VelocityComponent>();
    this->_r.register_components<DestroyableComponent>();
    this->_r.register_components<HealthComponent>();
    this->_r.register_components<ImmobileComponent>();
    this->_r.register_components<PositionComponent>();
    this->_r.register_components<WeaponComponent>();
    this->_r.register_components<DrawableComponent>();
    this->_r.register_components<CollideComponent>();
}

void World::register_all_system()
{
    this->_r.register_systems(&drawable_system);
    this->_r.register_systems(&velocity_system);
    this->_r.register_systems(&shooting_system);
    this->_r.register_systems(&wave_system);
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

RessourcesManager &World::getRessourcesManager()
{
    return (this->_manager);
}

registry &World::getRegistry()
{
    return (this->_r);
}

void World::create_laser(int x, int y, int x_velo, int y_velo, float refresh_time, float elapsed_time)
{
    Entity ent = this->_r.spawn_entity();
    this->_r.add_component<DrawableComponent>(ent, DrawableComponent("assets/r-typesheet1.gif", Vector4(104, 171, 80, 14)));
    this->_r.add_component<WeaponComponent>(ent, WeaponComponent("laser", 5, 15, 0.2));
    this->_r.add_component<VelocityComponent>(ent, VelocityComponent(x_velo, y_velo, refresh_time, elapsed_time));
    this->_r.add_component<PositionComponent>(ent, PositionComponent(x, y));
}

void World::create_player(std::string texture_path, Vector4 texture_rec, float x_scale, float y_scale, int pos_x,
    int pos_y, int hp, int speed_x, int speed_y, float refresh_time, KeyboardInput up, KeyboardInput down,
    KeyboardInput right, KeyboardInput left, MouseInput shoot)
{
    Entity ent = this->_r.spawn_entity();
    this->_r.add_component<DrawableComponent>(ent, DrawableComponent(texture_path, texture_rec, x_scale, y_scale));
    this->_r.add_component<PositionComponent>(ent, PositionComponent(pos_x, pos_y));
    this->_r.add_component<ImmobileComponent>(ent, ImmobileComponent(true, true));
    this->_r.add_component<CollideComponent>(ent, CollideComponent());
    this->_r.add_component<HealthComponent>(ent, (HealthComponent(hp)));
    this->_r.add_component<VelocityComponent>(ent, VelocityComponent(speed_x, speed_y, refresh_time));
    this->_r.add_component<ControllableComponent>(ent, ControllableComponent(up, down, right, left, shoot));
}

void World::create_enemy(std::string texture_path, Vector4 texture_rec, float x_scale, float y_scale, int pos_x, int pos_y,
    int speed_x, int speed_y, float refresh_time, float elapsed_time)
{
    Entity ent = this->_r.spawn_entity();
    this->_r.add_component<DrawableComponent>(ent, DrawableComponent(texture_path, texture_rec, x_scale, y_scale));
    this->_r.add_component<PositionComponent>(ent, PositionComponent(pos_x, pos_y));
    this->_r.add_component<ImmobileComponent>(ent, ImmobileComponent(false, false));
    this->_r.add_component<CollideComponent>(ent, CollideComponent());
    this->_r.add_component<WeaponComponent>(ent, WeaponComponent("meteor", 1, 1, 0));
    this->_r.add_component<DestroyableComponent>(ent, DestroyableComponent(true));
    this->_r.add_component<VelocityComponent>(ent, VelocityComponent(speed_x, speed_y, refresh_time, elapsed_time));
}