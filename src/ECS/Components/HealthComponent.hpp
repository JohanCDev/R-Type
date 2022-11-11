/**
 * @file HealthComponent.hpp
 * @author Cédric Corge (cedric.corge@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-10-16
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

/**
 * @brief Give an hp amount to the entity
 *
 */
struct HealthComponent {
    /**
     * @brief HP left of the component
     *
     */
    int hp;

    /**
     * @brief Max HP of the component
     *
     */
    size_t max_hp;

    /**
     * @brief Construct a new Health Component object
     *
     * @param hp_value Max HP of the component at creation
     */
    HealthComponent(int hp_value) : hp(hp_value), max_hp(hp_value){};
};
