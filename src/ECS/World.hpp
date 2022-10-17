/**
 * @file World.hpp
 * @author Cédric Corge (cedric.corge@epitech.eu)
 * @brief 
 * @version 0.1
 * @date 2022-10-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include "Registry.hpp"

#include "Systems/AllSystem.hpp"

#include <SFML/Graphics.hpp>

class World
{

    public:

        World(sf::VideoMode mode, std::string name);

        ~World();

        void register_all_component();
        void register_all_system();
        void register_all_assets();

        registry &getRegistry();
        RessourcesManager &getRessourcesManager();
        sf::RenderWindow &getWindow();
        sf::Clock &getClock();


    private:
        registry _r;
        RessourcesManager _manager;
        sf::RenderWindow _window;
        sf::Clock _clock;
};