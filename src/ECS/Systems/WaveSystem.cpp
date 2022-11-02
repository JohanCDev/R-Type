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
    float random_y = 0;

    if (world.getClock().getElapsedTime().asSeconds() > (elapsed_time + 3.0)) {
        elapsed_time += 3.0;
        random_y = static_cast<float>(std::rand() % world.getWindow().getSize().y);
    }
    return (0);
}
