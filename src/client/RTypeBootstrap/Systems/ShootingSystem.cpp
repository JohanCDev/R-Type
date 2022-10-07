/**
 * @file ShootingSystem.cpp
 * @author Cédric Corge (cedric.corge@epitech.eu)
 * @brief 
 * @version 0.1
 * @date 2022-10-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../registry.h"
#include "../RessourcesManager.hpp"
#include "../Components/WeaponComponent.h"
#include "../Components/PositionComponent.h"

int shooting_system(registry &r, RessourcesManager manager, sf::Clock clock)
{
    auto &weapons = r.get_components<WeaponComponent>();
    auto &positions = r.get_components<PositionComponent>();

    for (size_t i = 0; i < weapons.size(); ++i) {
        auto &weapon = weapons[i];
        auto &position = positions[i];
    }
    return (0);
}