/**
 * @file Lobby.cpp
 * @author Cédric Corge (cedric.corge@epitech.eu)
 * @brief 
 * @version 0.1
 * @date 2022-11-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "Lobby.hpp"

LobbyScene::LobbyScene() : _world(true), _init(false)
{
}

SceneScreen LobbyScene::run(NetworkClient &client, sf::RenderWindow &window)
{
    (void)client;
    sf::Event event;

    if (this->_init == false) {
        this->init_lobby(window);
        this->_init = true;
    }

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D)
            return (SceneScreen::GAME);
    }

    window.clear(sf::Color::Black);
    drawable_system(this->_world, window);
    window.display();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    return (SceneScreen::LOBBY);
}

void LobbyScene::init_lobby(sf::RenderWindow &window)
{
    this->_world.create_drawable_object("assets/background/lobby.png", Vector4i{0, 0, 1056, 672}, Vector2f{1.9, 1.6}, Vector2f{0, 0});
}