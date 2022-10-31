/**
 * @file Scene.hpp
 * @author Cédric Corge (cedric.corge@epitech.eu)
 * @brief 
 * @version 0.1
 * @date 2022-10-31
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include "../../ECS/World.hpp"

enum class SceneScreen : uint32_t {MENU = 0, GAME};

class IScene {

    public:

        virtual ~IScene() = default;

        virtual void run(World &world) = 0;

    private:
};