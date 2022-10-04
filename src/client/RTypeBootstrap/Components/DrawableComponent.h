#pragma once

struct DrawableComponent {
	std::string path;
	float x_scale;
	float y_scale;

	DrawableComponent(std::string texture_path, float xscale = 1.0, float yscale = 1.0)
	: path(texture_path), x_scale(xscale), y_scale(yscale) {}
};
