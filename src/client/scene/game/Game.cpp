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

GameScene::GameScene() : _world(true), _init(false)
{
}

void GameScene::run(NetworkClient &client, sf::RenderWindow &window, SceneScreen &current_screen)
{
    sf::Event event;
    Message<GameMessage> byeMsg;
    byeMsg.header.id = GameMessage::C2S_LEAVE;
    byeMsg << "Bybye";

    Message<GameMessage> shootMsg;
    shootMsg.header.id = GameMessage::C2S_SHOOT;
    shootMsg << "shoot";

    if (_init == false) {
        this->init_game(window);
        _init = true;
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
        client.processMessage(this->msg, _world, window, current_screen);
    }
    window.clear(sf::Color::Black);
    drawable_system(_world, window);
    velocity_system(_world);
    window.display();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

void GameScene::init_game(sf::RenderWindow &window)
{
    _world.create_skills(Vector2f{(float)window.getSize().x, (float)window.getSize().y});
    _world.create_settings(Vector2f{(float)window.getSize().x, (float)window.getSize().y});
    _world.create_healthbar(1, 1, Vector2f{(float)window.getSize().x, (float)window.getSize().y});
}
