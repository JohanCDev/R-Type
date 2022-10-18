/**
 * @file VelocityComponent.hpp
 * @author Tanguy Bellicha (tanguy.bellicha@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-10-18
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <SFML/Graphics.hpp>
#include <ctime>

struct VelocityComponent {
    int x = 0;
    int y = 0;
    float seconds;
    float coeff;

    VelocityComponent(int x_velo, int y_velo, float time_as_seconds, float elapsed_time = 0.0)
        : x(x_velo), y(y_velo), seconds(elapsed_time), coeff(time_as_seconds)
    {
    }
};
