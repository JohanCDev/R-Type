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

#include <ctime>

/**
 * @brief Give a velocity to the entity
 *
 */
struct VelocityComponent {
    Vector2i speed;
    float seconds;
    float coeff;

    /**
     * @brief Construct a new Velocity Component object
     *
     * @param x_velo
     * @param y_velo
     * @param time_as_seconds
     * @param elapsed_time
     */
    VelocityComponent(Vector2i speed_vec, float time_as_seconds, float elapsed_time = 0.0)
        : speed(speed_vec), seconds(elapsed_time), coeff(time_as_seconds)
    {
    }
};
