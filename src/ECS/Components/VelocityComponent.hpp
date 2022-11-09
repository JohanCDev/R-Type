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
    /**
     * @brief Speed of the component
     *
     */
    Vector2i speed;

    /**
     * @brief Seconds of acceleration
     *
     */
    float seconds;

    /**
     * @brief Coefficient of acceleration
     *
     */
    float coeff;

    /**
     * @brief Construct a new Velocity Component object
     *
     * @param speed_vec Vector containing the speed of the component
     * @param time_as_seconds Time of acceleration of the player
     * @param elapsed_time Elapsed time of the acceleration
     */
    VelocityComponent(Vector2i speed_vec, float time_as_seconds, float elapsed_time = 0.0)
        : speed(speed_vec), seconds(elapsed_time), coeff(time_as_seconds)
    {
    }
};
