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

#define _WIN32_WINNT 0x0601

#include <chrono>
#include <iostream>
#include <thread>
#include "../Common/Message/Message.hpp"
#include "../Common/Message/MessageType.hpp"
#include "client.hpp"
#include "scene/Scene.hpp"
#include "scene/game/Game.hpp"
#include "scene/menu/Menu.hpp"

#include "../ECS/World.hpp"

int main(void)
{
    //unsigned short port;
//
    //std::cin >> port;
    //NetworkClient client("localhost", "60000", port);
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "My window");

    std::srand(std::time(NULL));
    
    MenuScene menu;
    GameScene game;
    std::vector<std::reference_wrapper<IScene>> scenes;
    scenes.push_back(menu);
    scenes.push_back(game);
    SceneScreen actual_screen = SceneScreen::MENU;

    Message<GameMessage> shootMsg;
    shootMsg.header.id = GameMessage::C2S_SHOOT;
    shootMsg << "Shoot";

    while (window.isOpen()) {
        auto &scene = scenes[(int)actual_screen].get();
        actual_screen = scene.run(window);
    }
    return 0;
}
