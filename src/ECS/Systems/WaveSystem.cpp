/**
 * @file WaveSystem.cpp
 * @author Cédric Corge (cedric.corge@epitech.eu)
 * @brief 
 * @version 0.1
 * @date 2022-10-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../World.hpp"

static float elapsed_time = 0.0;

int wave_system(World &world)
{
    int random_y = 0;

    if (world.getClock().getElapsedTime().asSeconds() > (elapsed_time + 3.0)) {
        elapsed_time += 3.0;
        random_y = std::rand() % world.getWindow().getSize().y;
        world.create_enemy(GameObject::ENEMY, Vector2i{900, random_y}, Vector2i{-2, 0}, 0.04, world.getClock().getElapsedTime().asSeconds());
    }
    return (0);
}