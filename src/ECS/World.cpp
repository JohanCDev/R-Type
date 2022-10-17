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