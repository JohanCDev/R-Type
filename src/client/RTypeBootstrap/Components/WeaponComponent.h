#pragma once
#include <string>

struct WeaponComponent {
	std::string name;
	int damage;
	std::size_t cooldown_as_milliseconds;

	WeaponComponent(std::string weapon_name, int nb_damage, std::size_t cooldown)
		: damage(nb_damage), name(weapon_name), cooldown_as_milliseconds(cooldown) {};
};