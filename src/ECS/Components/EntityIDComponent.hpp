/**
 * @file EntityIDComponent.hpp
 * @author Tanguy Bellicha (tanguy.bellicha@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-10-25
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <stdio.h>

/**
 * @brief Store the entity ID
 *
 */
struct EntityIDComponent {
    /**
     * @brief ID of the entity
     *
     */
    size_t id;

    /**
     * @brief Construct a new Entity ID Component object
     *
     * @param entity_id ID to attribute
     */
    EntityIDComponent(size_t entity_id) : id(entity_id)
    {
    }

    /**
     * @brief Construct a new Entity ID Component object that will have 0 as ID
     *
     */
    EntityIDComponent() : id(0)
    {
    }
};
