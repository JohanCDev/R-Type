/**
 * @file SpeedComponent.hpp
 * @author Louis Maestre (louis.maestre@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-10-18
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

/**
 * @brief component speed for player
 *
 */
struct SpeedComponent {
    /**
     * @brief Speed value of the component
     *
     */
    int speed;

    /**
     * @brief Construct a new Speed Component object
     *
     * @param speed_vec speed augmentation
     */
    SpeedComponent(int speed_vec) : speed(speed_vec)
    {
    }
};
