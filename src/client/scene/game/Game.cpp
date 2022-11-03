/**
 * @file Game.cpp
 * @author Cédric Corge (cedric.corge@epitech.eu)
 * @brief 
 * @version 0.1
 * @date 2022-10-31
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "Game.hpp"

GameScene::GameScene() : _world(true), _connected(false)
{
}

void GameScene::run(NetworkClient &client, sf::RenderWindow &window, SceneScreen &actual_screen)
{
    sf::Event event;
    Message<GameMessage> byeMsg;
    byeMsg.header.id = GameMessage::C2S_LEAVE;
    byeMsg << "Bybye";

    Message<GameMessage> hiMsg;
    hiMsg.header.id = GameMessage::C2S_JOIN;
    hiMsg << "Lezgongue";

    Message<GameMessage> shootMsg;
    shootMsg.header.id = GameMessage::C2S_SHOOT;
    shootMsg << "shoot";

    if (_connected == false) {
        client.send(hiMsg);
        _connected = true;
    }

    while (window.pollEvent(event)) {
        handle_movement(_world, client, event);
        if (event.type == sf::Event::Closed) {
            window.close();
            client.send(byeMsg);
        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            client.send(shootMsg);
        }
    }

    while (client.HasMessages()) {
        this->msg = client.PopMessage();
        client.processMessage(msg, _world, window);
    }

    window.clear(sf::Color::Black);
    drawable_system(_world, window);
    velocity_system(_world);
    window.display();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}