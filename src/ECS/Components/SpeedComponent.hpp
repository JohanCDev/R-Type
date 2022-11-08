/**
 * @file VelocityComponent.hpp
 * @author Louis Maestre (louis.maestre@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-10-18
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <ctime>

#ifndef SPEEDCOMPONENT_HPP_
#define SPEEDCOMPONENT_HPP_

struct SpeedComponent {
    int speed;

    /**
     * @brief Construct a new Speed Component object
     * 
     * @param speed_vec
     */
    SpeedComponent(int speed_vec)
        : speed(speed_vec)
    {
    }
};

#endif /* !SPEEDCOMPONENT_HPP_ */
