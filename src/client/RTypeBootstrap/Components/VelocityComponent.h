#pragma once

#include <SFML/Graphics.hpp>
#include <ctime>

struct VelocityComponent {
	int x = 0;
	int y = 0;
	float seconds;
	float coeff;

	VelocityComponent(int x_velo, int y_velo, float time_as_seconds)
	: x(x_velo), y(y_velo), seconds(time_as_seconds), coeff(time_as_seconds) {}

};
