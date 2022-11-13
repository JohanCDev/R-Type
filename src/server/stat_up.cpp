/**
 * @file stat_up.cpp
 * @author Adam Djebar (adam.djebar@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-11-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "../ECS/Components/AllComponents.hpp"
#include "../ECS/World.hpp"

/**
 * @brief Augments the player's health
 *
 * @param world world to act on
 * @param e Player's entity ID
 */
void health_up(World &world, std::size_t &e)
{
    auto &health = world.getRegistry().get_components<HealthComponent>()[e];

    if (health && health.has_value()) {
        int health_diff = health->max_hp * 0.1;
        health->hp += health_diff;
        health->max_hp += health_diff;
    }
}

/**
 * @brief Augments the player's damage
 *
 * @param world world to act on
 * @param e Player's entity ID
 */
void damage_up(World &world, std::size_t &e)
{
    auto &weapon = world.getRegistry().get_components<WeaponComponent>()[e];

    if (weapon && weapon.has_value()) {
        weapon->damage *= 1.1;
    }
}

/**
 * @brief Augments the player's attack speed
 *
 * @param world world to act on
 * @param e Player's entity ID
 */
void atk_spd_up(World &world, std::size_t &e)
{
    auto &weapon = world.getRegistry().get_components<WeaponComponent>()[e];

    if (weapon && weapon.has_value()) {
        weapon->cooldown_as_milliseconds *= 0.9;
    }
}
/*
void spd_up(World &world, std::size_t &e)
{
    auto &max_spd = world.getRegistry().get_components<MaximumVelocityComponent>()[e];

    if (max_spd && max_spd.has_value()) {
        max_spd->x *= 1.1;
        max_spd->y *= 1.1;
    }
}
*/
static std::map<GameStat, std::function<void(World &, std::size_t &)>> statFunc = {{GameStat::HEALTH, health_up},
    {GameStat::DAMAGE, damage_up}, {GameStat::ATK_SPD, atk_spd_up}, /* {GameStat::SPD, spd_up}*/};

void stat_up(World &world, GameStat &stat, std::size_t &e)
{
    if (statFunc.contains(stat))
        statFunc[stat](world, e);
}
