/**
 * @file WaveSystem.cpp
 * @author Cédric Corge (cedric.corge@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-10-18
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "../Common/Message/Message.hpp"
#include "../Common/Message/MessageType.hpp"
#include "../ECS/Components/AllComponents.hpp"
#include "../ECS/World.hpp"
#include "game.hpp"
#include "server.hpp"

/**
 * @brief Create a boss in the world
 *
 * @param world World to act on
 * @param server Server structure
 * @param waves Waves information
 * @return Negative value if there is an error
 */
int create_boss(World &world, NetworkServer &server, waves_t &waves)
{
    Message<GameMessage> sending_msg;
    size_t entity_id = world.create_enemy(GameObject::BOSS_1,
        Vector2f{defaultValues[GameObject::BOSS_1].pos.x, defaultValues[GameObject::BOSS_1].pos.y},
        Vector2i{-defaultValues[GameObject::BOSS_1].spd, 0}, defaultValues[GameObject::BOSS_1].hp, 0.04f);
    world.getRegistry().add_component<EntityIDComponent>(
        world.getRegistry().entity_from_index(entity_id), EntityIDComponent{entity_id});

    std::cout << "Boss[" << entity_id << "]: created at Position{" << defaultValues[GameObject::BOSS_1].pos.x << ", "
              << defaultValues[GameObject::BOSS_1].pos.y << "}" << std::endl;
    sending_msg.header.id = GameMessage::S2C_ENTITY_NEW;
    sending_msg << GameObject::BOSS_1;
    sending_msg << entity_id;
    sending_msg << Vector2f{defaultValues[GameObject::BOSS_1].pos.x, defaultValues[GameObject::BOSS_1].pos.y};
    server.SendToAll(sending_msg);
    sending_msg.header.id = GameMessage::S2C_MOVEMENT;
    sending_msg << entity_id;
    sending_msg << Vector2i{-defaultValues[GameObject::BOSS_1].spd, 0};
    server.SendToAll(sending_msg);
    sending_msg.header.id = GameMessage::S2C_WAVE_STATUS;
    sending_msg << WaveStatus::BOSS_START;
    sending_msg << waves.nb_wave;
    server.SendToAll(sending_msg);
    return 0;
}

/**
 * @brief Create a wave in the world
 *
 * @param world World to act on
 * @param server Server structure
 * @param waves Waves information
 * @return Negative value if there is an error
 */
int create_wave(World &world, NetworkServer &server, waves_t &waves)
{
    Message<GameMessage> sending_msg;
    waves.in_wave = true;
    waves.nb_wave++;
    waves.clock.restart();
    if (waves.nb_wave > 0 && waves.nb_wave % DEFAULT_WAVE_FREQUENCY_BOSS == 0) {
        create_boss(world, server, waves);
        return 0;
    }
    if (waves.nb_wave > 1) {
        waves.base_difficulty *= DEFAULT_WAVE_DIFFICULTY_MULTIPLIER;
        waves.remaining_difficulty = waves.base_difficulty;
    }
    std::cout << "Wave " << waves.nb_wave << " started with difficulty " << waves.base_difficulty << std::endl;
    sending_msg.header.id = GameMessage::S2C_WAVE_STATUS;
    sending_msg << WaveStatus::START;
    sending_msg << waves.nb_wave;
    server.SendToAll(sending_msg);
    return 0;
}

void create_enemy(World &world, NetworkServer &server)
{
    size_t entity_id = 0;
    float random_y = rand() % 500 + 50;
    size_t random_enemy = rand() % ((size_t)GameObject::GAME_OBJECT_COUNT - (size_t)GameObject::ENEMY_FOCUS) + 3;
    Message<GameMessage> sending_msg;

    entity_id =
        world.create_enemy(GameObject::ENEMY_FOCUS, Vector2f{defaultValues[GameObject::ENEMY_FOCUS].pos.x, random_y},
            Vector2i{-defaultValues[GameObject::ENEMY_FOCUS].spd, 0}, defaultValues[GameObject::ENEMY_FOCUS].hp, 0.04f);
    world.getRegistry().add_component<EntityIDComponent>(
        world.getRegistry().entity_from_index(entity_id), EntityIDComponent{entity_id});
    std::cout << "Enemy[" << entity_id << "]: created at Position{" << defaultValues[GameObject::ENEMY_FOCUS].pos.x
              << ", " << random_y << "} with " << random_enemy << std::endl;
    sending_msg.header.id = GameMessage::S2C_ENTITY_NEW;
    sending_msg << GameObject::ENEMY_FOCUS;
    sending_msg << entity_id;
    sending_msg << Vector2f{defaultValues[GameObject::ENEMY_FOCUS].pos.x, random_y};
    server.SendToAll(sending_msg);
    sending_msg.header.id = GameMessage::S2C_MOVEMENT;
    sending_msg << entity_id;
    sending_msg << Vector2i{-defaultValues[GameObject::ENEMY_FOCUS].spd, 0};
    server.SendToAll(sending_msg);
}

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

int wave_system(World &world, NetworkServer &server, waves_t &waves)
{
    auto &teams = world.getRegistry().get_components<GameTeamComponent>();
    size_t remaining_enemies = 0;
    Message<GameMessage> sending_msg;

    for (size_t i = 0; i < teams.size(); ++i)
        if (teams[i] && teams[i]->team == GameTeam::ENEMY)
            remaining_enemies++;
    if (!waves.in_wave && waves.clock.getElapsedTime().asSeconds() > DEFAULT_WAVE_TIME_BETWEEN) {
        create_wave(world, server, waves);
        return 0;
    }
    if (waves.in_wave && waves.remaining_difficulty > 0
        && waves.clock.getElapsedTime().asSeconds() > DEFAULT_MINI_WAVE_TIME_BETWEEN) {
        size_t nb_enemy = 1;
        if (waves.base_difficulty >= 5)
            nb_enemy = rand() % (waves.base_difficulty / 5) + 1;
        if (nb_enemy > waves.remaining_difficulty)
            nb_enemy = waves.remaining_difficulty;
        for (size_t i = 0; i < nb_enemy; i++) {
            waves.remaining_difficulty--;
            create_enemy(world, server);
        }
        waves.clock.restart();
    }
    if (remaining_enemies == 0 && waves.in_wave && waves.remaining_difficulty == 0) {
        waves.in_wave = false;
        waves.clock.restart();
        std::cout << "Wave " << waves.nb_wave << " ended" << std::endl;
        sending_msg.header.id = GameMessage::S2C_WAVE_STATUS;
        sending_msg << WaveStatus::END;
        sending_msg << waves.nb_wave;
        server.SendToAll(sending_msg);
        level_up_system(world, server);
    }
    return 0;
}
