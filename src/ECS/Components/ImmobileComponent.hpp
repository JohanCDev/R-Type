/**
 * @file ImmobileComponent.hpp
 * @author Cédric CORGE (cedric.corge@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-09-27
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

/**
 * @brief Make the entity ignoring his velocity
 * 
 */
struct ImmobileComponent {
    bool x;
    bool y;

    /**
     * @brief Construct a new Immobile Component object
     * 
     * @param x_axis 
     * @param y_axis 
     */
    ImmobileComponent(bool x_axis, bool y_axis) : x(x_axis), y(y_axis){};
};
