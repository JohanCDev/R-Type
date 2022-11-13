/**
 * @file LevelUpSystem.cpp
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

int level_up_system(World &world, NetworkServer &server)
{
    auto &levels = world.getRegistry().get_components<LevelComponent>();
    auto &teams = world.getRegistry().get_components<GameTeamComponent>();
    Message<GameMessage> level_up_msg;

    std::size_t index = 0;

    for (auto &level : levels) {
        if (level && level.has_value()) {
            auto &team = teams[index];
            if (team && team.has_value() && team->team == GameTeam::PLAYER) {
                level->level++;
            }
        }
        index++;
    }
    level_up_msg.header.id = GameMessage::S2C_LEVEL_UP;
    level_up_msg << "ONE UP";
    server.SendToAll(level_up_msg);
    return 0;
}