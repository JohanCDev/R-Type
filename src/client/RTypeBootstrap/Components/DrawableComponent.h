#pragma once

#include <SFML/Graphics.hpp>

struct DrawableComponent {
	std::string path;
	float x_scale;
	float y_scale;

	DrawableComponent(std::string path, float x_scale = 1.0, float y_scale = 1.0)
	: path(path), x_scale(x_scale), y_scale(y_scale) {}
};
