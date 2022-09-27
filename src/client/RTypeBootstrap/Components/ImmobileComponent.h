/**
 * @file ImmobileComponent.h
 * @author Cédric CORGE (cedric.corge@epitech.eu)
 * @brief 
 * @version 0.1
 * @date 2022-09-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

struct ImmobileComponent {
	bool x;
    bool y;

	ImmobileComponent(bool x, bool y) : x(x), y(y) {};
};
