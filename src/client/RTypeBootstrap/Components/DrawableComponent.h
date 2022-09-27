#pragma once

#include <SFML/Graphics.hpp>

struct DrawableComponent {
	sf::Texture texture;
	sf::Sprite sprite;
	float x_scale;
	float y_scale;

	DrawableComponent(std::string path, float x_scale = 1.0, float y_scale = 1.0) : x_scale(x_scale), y_scale(y_scale) {
		texture.loadFromFile(path);
	};
};
