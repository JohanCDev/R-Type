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

enum class GameTeam : uint32_t { PLAYER, ENEMY, NEUTRAL, NONE };

struct GameTeamComponent {
    GameTeam team;

    GameTeamComponent(GameTeam entity_team) : team(entity_team)
    {
    }

    GameTeamComponent() : team(GameTeam::NONE)
    {
    }
};
