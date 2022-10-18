/**
 * @file loop.cpp
 * @author Tanguy BELLICHA (tanguy.bellicha@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-10-11
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "../ECS/Components/AllComponents.hpp"
#include "../ECS/Entity.hpp"
#include "../ECS/Registry.hpp"
#include "../ECS/ResourcesManager.hpp"
#include "../ECS/SparseArray.hpp"
#include "../Common/Message/MessageType.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <ctime>

#define DEFAULT_PLAYER_POS_X 50
#define DEFAULT_PLAYER_POS_Y 200
#define DEFAULT_PLAYER_SPD   4
#define DEFAULT_PLAYER_HP    100
#define DEFAULT_PLAYER_SCALE 2.0
#define DEFAULT_LASER_X_SPD  5
#define DEFAULT_LASER_Y_SPD  0
#define DEFAULT_ENEMY_HP     100
#define DEFAULT_ENEMY_ATK    40
#define DEFAULT_ENEMY_SPD    6
#define DEFAULT_ENEMY_SCALE  1.0
#define DEFAULT_KEY_TOP      KeyboardInput::Z
#define DEFAULT_KEY_RGT      KeyboardInput::D
#define DEFAULT_KEY_BOT      KeyboardInput::S
#define DEFAULT_KEY_LFT      KeyboardInput::Q
#define DEFAULT_KEY_SHOOT    MouseInput::Left_click

void player_joined(registry &r)
{
    std::cout << "Player Joined" << std::endl;
    r.create_player("", Vector4(375, 6, 21, 24), DEFAULT_PLAYER_SCALE, DEFAULT_PLAYER_SCALE, DEFAULT_PLAYER_POS_X,
        DEFAULT_PLAYER_POS_Y, DEFAULT_PLAYER_HP, 0, 0, 0.2, DEFAULT_KEY_TOP, DEFAULT_KEY_BOT, DEFAULT_KEY_RGT,
        DEFAULT_KEY_LFT, DEFAULT_KEY_SHOOT);
}

void player_left(registry &r)
{
    std::cout << "Player Left" << std::endl;
    (void)r;
    // r.kill_entity()
}

void player_moved(registry &r)
{
    std::cout << "Player Moved" << std::endl;
    (void)r;
}

void player_shot(registry &r)
{
    std::cout << "Player Shot" << std::endl;
    r.create_laser(1, 1, DEFAULT_LASER_X_SPD, DEFAULT_LASER_Y_SPD, 0.2, 0);
}

void create_enemy(registry &r)
{
    int random_y = rand() % 400 + 51;
    r.create_enemy("r-typesheet39.gif", Vector4(34, 2, 64, 64), DEFAULT_ENEMY_SCALE, DEFAULT_ENEMY_SCALE, 0, random_y, DEFAULT_ENEMY_SPD, 0, 0.2);
    std::cout << "Enemy Created" << std::endl;
}

static std::map<GameMessage, std::function<void(registry &)>> mapInit(void)
{
    std::map<GameMessage, std::function<void(registry &)>> mapFunc;

    mapFunc[GameMessage::C2S_JOIN] = player_joined;
    mapFunc[GameMessage::C2S_LEAVE] = player_left;
    // mapFunc[GameMessage::C2S_MOVEMENT] = player_moved;
    // mapFunc[GameMessage::C2S_SHOOT] = player_shot;
    return mapFunc;
}

void process_informations(GameMessage type, registry &r)
{
    std::map<GameMessage, std::function<void(registry &)>> mapFunc = mapInit();

    mapFunc[type](r);
}

// int idk()
// {
//     sf::Clock clock;
//     sf::Clock spawn_enemy;

//     // while (1) {
//         // Process informations
//         if (type != GameMessage::C2S_LEAVE)
//             process_informations(type, r);

//         if (spawn_enemy.getElapsedTime().asMilliseconds() > 800) {
//             if (i == 1)
//                 create_enemy(r);
//             spawn_enemy.restart();
//         }
//         // Create entities

//         // Update all entities

//         // Check collisions

//         // Update to clients
//     // }
//     return 0;
// }
