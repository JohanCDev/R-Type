/**
 * @file DoubleLaserComponent.hpp
 * @author Louis Maestre (louis.maestre@epitech.eu)
 * @brief
 * @version 0.1
 * @date
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

/**
 * @brief Make the entity destroyable
 *
 */
struct DoubleLaserComponent {
    /**
     * @brief Is the component destroyable
     *
     */
    bool _double;

    /**
     * @brief Construct a new Destroyable Component object
     *
     * @param destroy
     */
    DoubleLaserComponent(bool twoLaser) : _double(twoLaser)
    {
    }
};
