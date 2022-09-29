#pragma once

#include "../Input.hpp"

struct ControllableComponent {
	KeyboardInput up;
	KeyboardInput down;
	KeyboardInput right;
	KeyboardInput left;

	ControllableComponent(KeyboardInput up_key, KeyboardInput down_key, KeyboardInput right_key, KeyboardInput left_key)
		: up(up_key), down(down_key), right(right_key), left(left_key) {};
};
