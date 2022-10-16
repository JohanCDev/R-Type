/**
 * @file Destroyable.hpp
 * @author Cédric Corge (cedric.corge@epitech.eu)
 * @brief 
 * @version 0.1
 * @date 2022-10-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

struct DestroyableComponent {

    bool destroyable;

	DestroyableComponent(bool destroy) : destroyable(destroy) {}
};