#pragma once

#include <SFML/Graphics.hpp>
#include <ctime>

struct VelocityComponent {
	int x = 0;
	int y = 0;
	float seconds;
	float coeff;

	VelocityComponent(int x, int y, float seconds)
	: x(x), y(y), seconds(seconds), coeff(seconds) {}

};
