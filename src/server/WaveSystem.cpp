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
 * @brief Create a boss_1 in the world
 *
 * @param world World to act on
 * @param server Server structure
 * @return Negative value if there is an error
 */
int create_boss_1(World &world, NetworkServer &server)
{
    Message<GameMessage> sending_msg;
    size_t entity_id = world.create_enemy(GameObject::BOSS_1,
        Vector2f{defaultValues[GameObject::BOSS_1].pos.x, defaultValues[GameObject::BOSS_1].pos.y},
        Vector2i{-defaultValues[GameObject::BOSS_1].spd, 0}, defaultValues[GameObject::BOSS_1].hp, 0.04f);
    world.getRegistry().add_component<EntityIDComponent>(
        world.getRegistry().entity_from_index(entity_id), EntityIDComponent{entity_id});

    sending_msg.header.id = GameMessage::S2C_ENTITY_NEW;
    sending_msg << GameObject::BOSS_1;
    sending_msg << entity_id;
    sending_msg << Vector2f{defaultValues[GameObject::BOSS_1].pos.x, defaultValues[GameObject::BOSS_1].pos.y};
    server.SendToAll(sending_msg);
    sending_msg = Message<GameMessage>();
    sending_msg.header.id = GameMessage::S2C_MOVEMENT;
    sending_msg << entity_id;
    sending_msg << Vector2i{-defaultValues[GameObject::BOSS_1].spd, 0};
    server.SendToAll(sending_msg);
    sending_msg = Message<GameMessage>();
    sending_msg.header.id = GameMessage::S2C_WAVE_STATUS;
    sending_msg << WaveStatus::BOSS_START;
    sending_msg << (size_t)DEFAULT_WAVE_FREQUENCY_BOSS * 1;
    server.SendToAll(sending_msg);
    sending_msg = Message<GameMessage>();
    return 0;
}

static std::map<GameObject, std::function<void(World &, NetworkServer &)>> map_create_boss = {
    {GameObject::BOSS_1, create_boss_1}};

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
    GameObject type;

    waves.in_wave = true;
    waves.nb_wave++;
    waves.clock.restart();
    if (waves.nb_wave > 0 && waves.nb_wave % DEFAULT_WAVE_FREQUENCY_BOSS == 0) {
        // type = (GameObject)((size_t)GameObject::BOSS_1 + num_boss - 1);
        type = GameObject::BOSS_1;
        map_create_boss[type](world, server);
        return 0;
    }
    if (waves.nb_wave > 1) {
        waves.base_difficulty *= DEFAULT_WAVE_DIFFICULTY_MULTIPLIER;
        waves.remaining_difficulty = waves.base_difficulty;
    }
    sending_msg.header.id = GameMessage::S2C_WAVE_STATUS;
    sending_msg << WaveStatus::START;
    sending_msg << waves.nb_wave;
    server.SendToAll(sending_msg);
    return 0;
}

void create_enemy(World &world, NetworkServer &server)
{
    size_t entity_id = 0;
    float random_y = rand() % 880 + 100;
    GameObject type = (GameObject)(rand() % (((size_t)GameObject::ENEMY_SNIPER + 1) - (size_t)GameObject::ENEMY_FOCUS)
        + (size_t)GameObject::ENEMY_FOCUS);
    Message<GameMessage> sending_msg;

    entity_id = world.create_enemy(type, Vector2f{defaultValues[type].pos.x, random_y},
        Vector2i{-defaultValues[type].spd, 0}, defaultValues[type].hp, 0.04f);
    world.getRegistry().add_component<EntityIDComponent>(
        world.getRegistry().entity_from_index(entity_id), EntityIDComponent{entity_id});
    sending_msg.header.id = GameMessage::S2C_ENTITY_NEW;
    sending_msg << type;
    sending_msg << entity_id;
    sending_msg << Vector2f{defaultValues[type].pos.x, random_y};
    server.SendToAll(sending_msg);
    sending_msg = Message<GameMessage>();
    sending_msg.header.id = GameMessage::S2C_MOVEMENT;
    sending_msg << entity_id;
    sending_msg << Vector2i{-defaultValues[type].spd, 0};
    server.SendToAll(sending_msg);
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
        sending_msg.header.id = GameMessage::S2C_WAVE_STATUS;
        sending_msg << WaveStatus::END;
        sending_msg << waves.nb_wave;
        server.SendToAll(sending_msg);
        level_up_system(world, server);
    }
    return 0;
}
