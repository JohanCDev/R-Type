/**
 * @file LevelComponent.hpp
 * @author Adam Djebar (adam.djebar@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-11-08
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

/**
 * @brief Define a level for an entity
 *
 */
struct LevelComponent {
    /**
     * @brief Level of an entity
     *
     */
    uint32_t level = 0;

     /**
     * @brief Amount of points spent
     *
     */
    uint32_t spent_points = 0;
};
