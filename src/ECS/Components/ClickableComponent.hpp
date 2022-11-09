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

struct ClickableComponent {
    std::function<void(World &, SceneScreen &, NetworkClient &)> callback;

    ClickableComponent(std::function<void(World &, SceneScreen &, NetworkClient &)> callback_func)
        : callback(callback_func)
    {
    }
};
