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

GameScene::GameScene() : _client("localhost", "60000", 1432), _world(true), _connected(false)
{
}

SceneScreen GameScene::run(sf::RenderWindow &window)
{
    sf::Event event;
    Message<GameMessage> byeMsg;
    byeMsg.header.id = GameMessage::C2S_LEAVE;
    byeMsg << "Bybye";

    Message<GameMessage> hiMsg;
    hiMsg.header.id = GameMessage::C2S_JOIN;
    hiMsg << "Lezgongue";

    if (_connected == false) {
        this->_client.send(hiMsg);
        _connected = true;
    }

    while (window.pollEvent(event)) {
        handle_movement(_world, _client, event);
        if (event.type == sf::Event::Closed) {
            window.close();
            this->_client.send(byeMsg);
        }
    }

    while (this->_client.HasMessages()) {
        this->msg = this->_client.PopMessage();
        this->_client.processMessage(msg, _world, window);
    }

    window.clear(sf::Color::Black);
    drawable_system(_world, window);
    velocity_system(_world);
    window.display();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    return (SceneScreen::GAME);
}