/**
 * @file ClientIDComponent.hpp
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
 * @brief Store the client ID
 *
 */
struct ClientIDComponent {
    size_t id;

    ClientIDComponent(size_t assign_id) : id(assign_id){};

    ClientIDComponent() : id(-1) {}
};
