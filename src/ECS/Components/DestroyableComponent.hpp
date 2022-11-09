/**
 * @file DestroyableComponent.hpp
 * @author Cédric Corge (cedric.corge@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-10-11
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

/**
 * @brief Make the entity destroyable
 *
 */
struct DestroyableComponent {
    /**
     * @brief Is the component destroyable
     *
     */
    bool destroyable;

    /**
     * @brief Construct a new Destroyable Component object
     *
     * @param destroy
     */
    DestroyableComponent(bool destroy) : destroyable(destroy)
    {
    }
};
