/**
 * @file WeaponComponent.hpp
 * @author Tanguy Bellicha (tanguy.bellicha@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-10-18
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <string>
#include "../Input.hpp"

/**
 * @brief Make the entity able to shoot
 * 
 */
struct WeaponComponent {
    std::string name;
    Vector2i stat;
    std::size_t cooldown_as_milliseconds;

    WeaponComponent(std::string weapon_name, Vector2i stat_vec, std::size_t cooldown)
        : name(weapon_name), stat(stat_vec), cooldown_as_milliseconds(cooldown){};
};
