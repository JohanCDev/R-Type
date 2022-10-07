#pragma once
#include <string>

#include "../Input.hpp"

struct WeaponComponent {
	std::string name;
	int damage;
	int speed_travel;
	std::size_t cooldown_as_milliseconds;

	WeaponComponent(std::string weapon_name, int nb_damage, int travel_speed, std::size_t cooldown)
		: damage(nb_damage), name(weapon_name), speed_travel(travel_speed), cooldown_as_milliseconds(cooldown) {};
};