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

void LobbyScene::run(NetworkClient &client, sf::RenderWindow &window, SceneScreen &actual_screen)
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
            actual_screen = SceneScreen::GAME;
    }

    window.clear(sf::Color::Black);
    drawable_system(this->_world, window);
    window.display();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

void LobbyScene::init_lobby(sf::RenderWindow &window)
{
    this->_world.create_text("CHOOSE YOUR SPACESHIP", "assets/font/EMINOR-BlackItalic.ttf", 70, Vector2f{window.getSize().x / 2 - 367.5, 200.0});
    this->_world.create_drawable_object("assets/background/lobby.png", Vector4i{0, 0, 1056, 672}, Vector2f{1.9, 1.6}, Vector2f{0, 0});

    this->_world.create_drawable_object("assets/SpaceShip/ship_armored_spritesheet.png", Vector4i{0, 0, 128, 128}, Vector2f{2.0, 2.0}, Vector2f{164, (float)window.getSize().y / 2});
    this->_world.create_drawable_object("assets/SpaceShip/ship_damage_spritesheet.png", Vector4i{0, 0, 128, 128}, Vector2f{2.0, 2.0}, Vector2f{600,  (float)window.getSize().y / 2});
    this->_world.create_drawable_object("assets/SpaceShip/ship_engineer_spritesheet.png", Vector4i{0, 0, 128, 128}, Vector2f{2.0, 2.0}, Vector2f{1000, (float)window.getSize().y / 2});
    this->_world.create_drawable_object("assets/SpaceShip/ship_sniper_spritesheet.png", Vector4i{0, 0, 128, 128}, Vector2f{2.0, 2.0}, Vector2f{1500, (float)window.getSize().y / 2});
}