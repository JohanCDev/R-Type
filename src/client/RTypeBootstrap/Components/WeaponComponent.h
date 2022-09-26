#pragma once
#include <string>

struct WeaponComponent {
	std::string name;
	int damage;
	std::size_t cooldown_as_milliseconds;

	WeaponComponent(std::string name, int damage, std::size_t cooldown_as_milliseconds)
		: damage(damage), name(name), cooldown_as_milliseconds(cooldown_as_milliseconds) {};
};