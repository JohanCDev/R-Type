/**
 * @file ClientIDComponent.hpp
 * @author Tanguy Bellicha (you@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-10-25
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <stdio.h>

struct ClientIDComponent {
    size_t id;

    ClientIDComponent(size_t assign_id) : id(assign_id){};
};
