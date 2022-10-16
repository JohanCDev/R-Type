/**
 * @file PositionComponent.hpp
 * @author Cédric Corge (cedric.corge@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-10-16
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

struct PositionComponent {
    int x = 0;
    int y = 0;

    PositionComponent(int x_pos, int y_pos) : x(x_pos), y(y_pos){};
};
