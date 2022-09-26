#pragma once

struct HitBoxComponent {
	int width;
	int height;

	HitBoxComponent(int width, int height)
		: width(width), height(height) {};
};