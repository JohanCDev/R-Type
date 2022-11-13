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
     * @brief Is it activated
     *
     */
    bool _double;

    /**
     * @brief Construct a new Destroyable Component object
     *
     * @param twoLaser Is the component activated
     */
    DoubleLaserComponent(bool twoLaser) : _double(twoLaser)
    {
    }
};
