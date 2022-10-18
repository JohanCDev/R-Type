/**
 * @file ControllableComponent.hpp
 * @author Cédric Corge (cedric.corge@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-10-07
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "../Input.hpp"

struct ControllableComponent {
    KeyboardInput up;
    KeyboardInput down;
    KeyboardInput right;
    KeyboardInput left;
    MouseInput shoot;

    ControllableComponent(KeyboardInput up_key, KeyboardInput down_key, KeyboardInput right_key, KeyboardInput left_key,
        MouseInput shoot_key)
        : up(up_key), down(down_key), right(right_key), left(left_key), shoot(shoot_key){};
};
