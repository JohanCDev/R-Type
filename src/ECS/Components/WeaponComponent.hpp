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
    /**
     * @brief Name of the weapon
     *
     */
    std::string name;

    /**
     * @brief Damage of the weapon
     *
     */
    uint32_t damage;

    /**
     * @brief Construct a new Weapon Component object
     *
     * @param weapon_name name of the weapon
     * @param damage_amount Damage of the weapon
     * @param cooldown Fire rate of the weapon
     */
    WeaponComponent(std::string weapon_name, uint32_t damage_amount, std::size_t cooldown)
        : name(weapon_name), damage(damage_amount), cooldown_as_milliseconds(cooldown){};

    /**
     * @brief Stats of the weapon
     *
     * First value is the damage that the weapon will cause
     * Second is the Fire Frequency
     *
     */
    Vector2i stat;

    /**
     * @brief Cooldown of the weapon
     *
     * Will disable the fact that the player is always shooting
     *
     */
    std::size_t cooldown_as_milliseconds;

    /**
     * @brief Construct a new Weapon Component object
     *
     * @param weapon_name Name of the weapon
     * @param stat_vec Stats of the weapon {Damage, Fire Frequency}
     * @param cooldown Cooldown in ms of the weapon
     */
    WeaponComponent(std::string weapon_name, Vector2i stat_vec, std::size_t cooldown)
        : name(weapon_name), stat(stat_vec), cooldown_as_milliseconds(cooldown){};
};
