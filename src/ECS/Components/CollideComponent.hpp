/**
 * @file CollideComponent.hpp
 * @author Tanguy Bellicha (tanguy.bellicha@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-10-18
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

/**
 * @brief Make the entity able to collide with others
 *
 */
struct CollideComponent {
    /**
     * @brief Does the component collide ?
     *
     */
    bool collide;

    CollideComponent() : collide(false)
    {
    }
};
