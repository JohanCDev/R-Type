/**
 * @file AllSystem.hpp
 * @author Cédric Corge (cedric.corge@epitech.eu)
 * @brief 
 * @version 0.1
 * @date 2022-10-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include "../World.hpp"

int drawable_system(World &world);
int controllable_system(World &world, sf::Event event);
int shooting_system(World &world);
int velocity_system(World &world);
int wave_system(World &world);