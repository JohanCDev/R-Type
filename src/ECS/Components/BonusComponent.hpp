/**
 * @file BonusComponent.hpp
 * @author Louis Maestre (louis.maestre@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-10-18
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <chrono>
#include <string>

/**
 * @brief enum to get bonus effect
 *
 */
enum Bonus : uint32_t { ATTACK, ATTACK_SPEED, HEAL, SPEED, DOUBLE };

/**
 * @brief Make the entity able to get bonus
 *
 */
struct BonusComponent {
    /**
     * @brief Bonus name of the component
     *
     */
    Bonus bonus_name;

    /**
     * @brief Chrono of the bonus
     *
     */
    std::chrono::time_point<std::chrono::steady_clock> _time;

    /**
     * @brief Construct a new bonus Component object
     *
     * @param nameBonus bonus name
     * @param time Display time of the bonus
     */
    BonusComponent(Bonus nameBonus, std::chrono::time_point<std::chrono::steady_clock> time)
        : bonus_name(nameBonus), _time(time){};
};