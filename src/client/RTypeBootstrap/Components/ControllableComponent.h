#pragma once

#include <SFML/Window.hpp>

struct ControllableComponent {
	sf::Keyboard::Key up;
	sf::Keyboard::Key down;
	sf::Keyboard::Key right;
	sf::Keyboard::Key left;

	ControllableComponent(sf::Keyboard::Key up, sf::Keyboard::Key down, sf::Keyboard::Key right, sf::Keyboard::Key left)
		: up(up), down(down), right(right), left(left) {};
};
