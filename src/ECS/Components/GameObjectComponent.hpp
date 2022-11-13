/**
 * @file GameObjectComponent.hpp
 * @author Tanguy Bellicha (tanguy.bellicha@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-11-07
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "../../Common/Message/MessageType.hpp"

/**
 * @brief Game Object of entity
 *
 */
struct GameObjectComponent {
    /**
     * @brief Type of the Game Object
     *
     */
    GameObject type;

    /**
     * @brief Construct a new Game Object Component object
     *
     * @param entity_type Type to give to the entity
     */
    GameObjectComponent(GameObject entity_type) : type(entity_type)
    {
    }
};
