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
        this->init_lobby(window, client);
        this->_init = true;
    }

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D)
            actual_screen = SceneScreen::GAME;
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            clickable_system(this->_world, Vector2i{sf::Mouse::getPosition().x, sf::Mouse::getPosition().y}, actual_screen, client);
        }
    }

    window.clear(sf::Color::Black);
    drawable_system(this->_world, window);
    window.display();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

void LobbyScene::init_lobby(sf::RenderWindow &window, NetworkClient &client)
{
    this->_world.create_text("CHOOSE YOUR SPACESHIP", "assets/font/EMINOR-BlackItalic.ttf", 70, Vector2f{(float)window.getSize().x / 2 - 367.5f, 200.0});
    this->_world.create_text("PLAYER: 1/4", "assets/font/EMINOR-BlackItalic.ttf", 50, Vector2f{(float)window.getSize().x - 350.0f, 100.0f});
    this->_world.create_drawable_object("assets/background/lobby.png", Vector4i{0, 0, 1056, 672}, Vector4i{255, 255, 255, 255}, Vector2f{1.9, 1.6}, Vector2f{0, 0});

    this->_world.create_button("assets/SpaceShip/ship_armored_spritesheet.png", Vector4i{0, 0, 128, 128}, Vector2f{2.0, 2.0}, Vector2f{164, (float)window.getSize().y / 2}, &select_armored_ship);
    this->_world.create_button("assets/SpaceShip/ship_damage_spritesheet.png", Vector4i{0, 0, 128, 128}, Vector2f{2.0, 2.0}, Vector2f{600,  (float)window.getSize().y / 2}, &select_damage_ship);
    this->_world.create_button("assets/SpaceShip/ship_engineer_spritesheet.png", Vector4i{0, 0, 128, 128}, Vector2f{2.0, 2.0}, Vector2f{1000, (float)window.getSize().y / 2}, &select_engineer_ship);
    this->_world.create_button("assets/SpaceShip/ship_sniper_spritesheet.png", Vector4i{0, 0, 128, 128}, Vector2f{2.0, 2.0}, Vector2f{1500, (float)window.getSize().y / 2}, &select_sniper_ship);

    if (client.getHost() == true) {
        Vector2f pos = {(float)window.getSize().x / 2 - 131.4f, (float)window.getSize().y - 124.0f};
        this->_world.create_button("assets/background/bg-boutton.png", Vector4i{41, 28, 657, 284}, Vector2f{0.4, 0.4}, pos, &launch_game);
    }
}