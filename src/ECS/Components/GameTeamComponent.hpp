/**
 * @file GameTeamComponent.hpp
 * @author Cédric Corge (cedric.corge@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-10-27
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

/**
 * @brief Available teams
 *
 */
enum class GameTeam : uint32_t { PLAYER, ENEMY, NEUTRAL, NONE };

/**
 * @brief Define the team of the entity
 *
 */
struct GameTeamComponent {
    /**
     * @brief Team of the component
     *
     */
    GameTeam team;

    /**
     * @brief Construct a new Game Team Component object
     *
     * @param entity_team Team of the Component
     */
    GameTeamComponent(GameTeam entity_team) : team(entity_team)
    {
    }

    /**
     * @brief Construct a new Game Team Component object with no GameTeam
     *
     */
    GameTeamComponent() : team(GameTeam::NONE)
    {
    }
};
