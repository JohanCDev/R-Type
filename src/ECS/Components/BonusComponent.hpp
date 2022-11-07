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
 * @brief Make the entity able to shoot
 * 
 */

enum Bonus : uint32_t {ATTACK, ATTACK_SPEED, HEAL, SPEED};

struct BonusComponent {
    // std::string name;
    Bonus bonus_name;

    /**
     * @brief Construct a new Health Component object
     *
     * @param hp_value
     */
    BonusComponent(Bonus nameBonus) : bonus_name(nameBonus) {};
};