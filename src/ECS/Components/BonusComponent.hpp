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

    /**
     * @brief Construct a new bonus Component object
     *
     * @param nameBonus
     */
    BonusComponent(Bonus nameBonus) : bonus_name(nameBonus) {};
};