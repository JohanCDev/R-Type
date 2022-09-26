#pragma once

#include <SFML/Graphics.hpp>

struct DrawableComponent {
	sf::Texture texture;
	sf::Sprite sprite;

	DrawableComponent(std::string path) {
		texture.loadFromFile(path);
	};
};
