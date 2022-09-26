#pragma once

#include <SFML/Graphics.hpp>

struct VelocityComponent {
	int x = 0;
	int y = 0;
	sf::Clock clock;
	float seconds;

	VelocityComponent(int x, int y, float seconds)
		: x(x), y(y), seconds(seconds) {};
};
