#pragma once

#include "../Input.hpp"

struct ControllableComponent {
	KeyboardInput up;
	KeyboardInput down;
	KeyboardInput right;
	KeyboardInput left;

	ControllableComponent(KeyboardInput up, KeyboardInput down, KeyboardInput right, KeyboardInput left)
		: up(up), down(down), right(right), left(left) {};
};
