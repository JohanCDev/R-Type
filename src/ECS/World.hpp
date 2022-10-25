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
#include <map>

class World
{

    public:

        World(sf::VideoMode mode, std::string name);

        ~World();

        void register_all_component();
        void register_all_system();
        void register_all_assets();

        /**
         * @brief Create a laser entity
         * 
         * @param object
         * @param x 
         * @param y 
         * @param x_velo 
         * @param y_velo 
         * @param refresh_time 
         * @param elapsed_time 
         */
        void create_laser(GameObject object, int x, int y, int x_velo, int y_velo, float refresh_time, float elapsed_time);

        /**
         * @brief Create a player entity
         * 
         * @param object
         * @param pos_x 
         * @param pos_y 
         * @param speed_x 
         * @param speed_y 
         * @param refresh_time 
         */
        void create_player(GameObject object, int pos_x, int pos_y, int speed_x, int speed_y, float refresh_time);

        /**
         * @brief Create a enemy entity
         * 
         * @param texture_path 
         * @param texture_rec 
         * @param x_scale 
         * @param y_scale 
         * @param pos_x 
         * @param pos_y 
         * @param speed_x 
         * @param speed_y 
         * @param refresh_time 
         * @param elapsed_time 
         */
        void create_enemy(std::string texture_path, Vector4 texture_rec, float x_scale, float y_scale, int pos_x, int pos_y,
        int speed_x, int speed_y, float refresh_time, float elapsed_time);

        void register_all_drawable_object();

        registry &getRegistry();
        ResourcesManager &getResourcesManager();
        sf::RenderWindow &getWindow();
        sf::Clock &getClock();


    private:
        registry _r;
        ResourcesManager _manager;
        sf::RenderWindow _window;
        sf::Clock _clock;
        std::map<GameObject, DrawableComponent> _drawMap;
};