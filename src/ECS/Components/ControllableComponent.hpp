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

/**
 * @brief Make the entity controllable
 *
 */
struct ControllableComponent {
    /**
     * @brief KeyboardInput allowing the player to go up
     *
     */
    KeyboardInput up;
    /**
     * @brief KeyboardInput allowing the player to go down
     *
     */
    KeyboardInput down;
    /**
     * @brief KeyboardInput allowing the player to go right
     *
     */
    KeyboardInput right;
    /**
     * @brief KeyboardInput allowing the player to go left
     *
     */
    KeyboardInput left;
    /**
     * @brief MouseInput allowing the player to shoot
     *
     */
    MouseInput shoot;

    /**
     * @brief Construct a new Controllable Component object
     *
     * @param up_key KeyboardInput allowing the player to go up
     * @param down_key KeyboardInput allowing the player to go down
     * @param right_key KeyboardInput allowing the player to go right
     * @param left_key KeyboardInput allowing the player to go left
     * @param shoot_key MouseInput allowing the player to shoot
     */
    ControllableComponent(KeyboardInput up_key, KeyboardInput down_key, KeyboardInput right_key, KeyboardInput left_key,
        MouseInput shoot_key)
        : up(up_key), down(down_key), right(right_key), left(left_key), shoot(shoot_key){};
};
