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

#include <string>
#include <chrono>

/**
 * @brief enum to get bonus effect
 * 
 */
enum Bonus : uint32_t {ATTACK, ATTACK_SPEED, HEAL, SPEED};


/**
 * @brief Make the entity able to get bonus
 * 
 */
struct BonusComponent {
    Bonus bonus_name;
    std::chrono::time_point<std::chrono::steady_clock> _time;

    /**
     * @brief Construct a new bonus Component object
     *
     * @param nameBonus
     */
    BonusComponent(Bonus nameBonus, std::chrono::time_point<std::chrono::steady_clock> time) : bonus_name(nameBonus), _time(time) {};
};