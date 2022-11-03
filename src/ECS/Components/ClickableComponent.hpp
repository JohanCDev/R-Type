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

struct ClickableComponent {

    std::function<void(void)> callback;

    ClickableComponent() {}

};