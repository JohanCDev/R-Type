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

        void create_laser(int x, int y, int x_velo, int y_velo, float refresh_time, float elapsed_time);
        void create_player(std::string texture_path, Vector4 texture_rec, float x_scale, float y_scale, int pos_x,
        int pos_y, int hp, int speed_x, int speed_y, float refresh_time, KeyboardInput up, KeyboardInput down,
        KeyboardInput right, KeyboardInput left, MouseInput shoot);
        void create_enemy(std::string texture_path, Vector4 texture_rec, float x_scale, float y_scale, int pos_x, int pos_y,
        int speed_x, int speed_y, float refresh_time, float elapsed_time);

        registry &getRegistry();
        ResourcesManager &getResourcesManager();
        sf::RenderWindow &getWindow();
        sf::Clock &getClock();


    private:
        registry _r;
        ResourcesManager _manager;
        sf::RenderWindow _window;
        sf::Clock _clock;
};