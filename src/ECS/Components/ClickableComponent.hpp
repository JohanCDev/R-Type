/**
 * @file ClickableComponent.hpp
 * @author Cédric Corge (cedric.corge@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-11-03
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <functional>

class World;
enum class SceneScreen : uint32_t;
class NetworkClient;

/**
 * @brief Makes an entity clickable
 *
 */
struct ClickableComponent {
    /**
     * @brief Callback function of the button
     *
     */
    std::function<void(World &, SceneScreen &, NetworkClient &, float &)> callback;

    /**
     * @brief Construct a new Clickable Component object
     *
     * @param callback_func callback function to assign to the component
     */
    ClickableComponent(std::function<void(World &, SceneScreen &, NetworkClient &, float &)> callback_func)
        : callback(callback_func)
    {
    }
};
