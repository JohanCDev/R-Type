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

int create_boss(World &world, NetworkServer &server, waves_t &waves)
{
    Message<GameMessage> sending_msg;
    size_t entity_id =
        world.create_enemy(GameObject::ENEMY_FOCUS, Vector2f{800, 300}, Vector2i{-DEFAULT_ENEMY_SPD, 0}, 200, 0.04f);
    world.getRegistry().add_component<EntityIDComponent>(
        world.getRegistry().entity_from_index(entity_id), EntityIDComponent{entity_id});

    std::cout << "Boss[" << entity_id << "]: created at Position{800, 300}" << std::endl;
    sending_msg.header.id = GameMessage::S2C_ENTITY_NEW;
    sending_msg << GameObject::ENEMY_FOCUS;
    sending_msg << entity_id;
    sending_msg << Vector2f{800, 300};
    server.SendToAll(sending_msg);
    sending_msg.header.id = GameMessage::S2C_MOVEMENT;
    sending_msg << entity_id;
    sending_msg << Vector2i{-DEFAULT_ENEMY_SPD, 0};
    server.SendToAll(sending_msg);
    sending_msg.header.id = GameMessage::S2C_WAVE_STATUS;
    sending_msg << WaveStatus::BOSS_START;
    sending_msg << waves.nb_wave;
    server.SendToAll(sending_msg);
    return 0;
}

int create_wave(World &world, NetworkServer &server, waves_t &waves)
{
    Message<GameMessage> sending_msg;
    waves.in_wave = true;
    waves.nb_wave++;
    waves.clock.restart();
    if (waves.nb_wave > 0 && waves.nb_wave % DEFAULT_FREQUENCY_BOSS_WAVE == 0) {
        create_boss(world, server, waves);
        return 0;
    }
    waves.base_difficulty *= 1.4;
    waves.remaining_difficulty = waves.base_difficulty;
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
    size_t random_enemy = rand() % ((size_t)GameObject::GAME_OBJECT_COUNT - (size_t)GameObject::ENEMY_FOCUS) + 2;
    Message<GameMessage> sending_msg;

    entity_id = world.create_enemy(
        (GameObject)random_enemy, Vector2f{800.0f, random_y}, Vector2i{-DEFAULT_ENEMY_SPD, 0}, DEFAULT_ENEMY_HP, 0.04f);
    world.getRegistry().add_component<EntityIDComponent>(
        world.getRegistry().entity_from_index(entity_id), EntityIDComponent{entity_id});
    std::cout << "Enemy[" << entity_id << "]: created at Position{800, " << random_y << "}" << std::endl;
    sending_msg.header.id = GameMessage::S2C_ENTITY_NEW;
    sending_msg << GameObject::ENEMY_FOCUS;
    sending_msg << entity_id;
    sending_msg << Vector2f{800.0f, random_y};
    server.SendToAll(sending_msg);
    sending_msg.header.id = GameMessage::S2C_MOVEMENT;
    sending_msg << entity_id;
    sending_msg << Vector2i{-DEFAULT_ENEMY_SPD, 0};
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
    if (!waves.in_wave && waves.clock.getElapsedTime().asSeconds() > 5) {
        create_wave(world, server, waves);
        return 0;
    }
    if (waves.in_wave && waves.remaining_difficulty > 0 && waves.clock.getElapsedTime().asSeconds() > 0.8) {
        size_t nb_enemy = rand() % (waves.base_difficulty / 5) + 1;
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
    }
    return 0;
}
