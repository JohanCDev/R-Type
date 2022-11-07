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

struct GameObjectComponent {
    GameObject type;

    GameObjectComponent(GameObject entity_type) : type(entity_type)
    {
    }
};
