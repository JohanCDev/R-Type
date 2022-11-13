/**
 * @file main.cpp
 * @author Cédric Corge (cedric.corge@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-10-16
 *
 * @copyright Copyright (c) 2022
 *
 */

/**
 * @brief Define the WIN32 version
 */
#define _WIN32_WINNT 0x0601

#include <chrono>
#include <iostream>
#include <thread>
#include "../Common/Message/Message.hpp"
#include "../Common/Message/MessageType.hpp"
#include "../ECS/World.hpp"
#include "client.hpp"
#include "proto.hpp"
#include "scene/game/Game.hpp"
#include "scene/lobby/Lobby.hpp"
#include "scene/menu/Menu.hpp"
#include "scene/option/Option.hpp"

/**
 * @brief Main function
 *
 * @return int
 */
int main(void)
{
    unsigned int port = 0;
    std::cin >> port;
    std::srand(std::time(NULL));

    NetworkClient client("localhost", "60000", port);

#if __APPLE__
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "My window");
#else
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "My window", sf::Style::Fullscreen);
#endif
    MenuScene menu;
    GameScene game;
    LobbyScene lobby;
    OptionScene option;

    std::vector<std::reference_wrapper<IScene>> scenes;
    scenes.push_back(menu);
    scenes.push_back(lobby);
    scenes.push_back(game);
    scenes.push_back(option);
    SceneScreen current_screen = SceneScreen::MENU;
    float volume = 50.0f;

    while (window.isOpen()) {
        auto &scene = scenes[(int)current_screen].get();
        scene.run(client, window, current_screen, volume);
    }
    return 0;
}
