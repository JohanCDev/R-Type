/**
 * @file Menu.cpp
 * @author Cédric Corge (cedric.corge@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-10-31
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "Menu.hpp"

MenuScene::MenuScene() : _world(true), _init(false)
{
}

void MenuScene::run(NetworkClient &client, sf::RenderWindow &window, SceneScreen &current_screen, float &volume)
{
    (void)client;
    sf::Event event;

    if (this->_init == false) {
        this->_world.register_menu_assets();
        music_system(this->_world, "./assets/music/mainTheme.wav", volume);
        this->init_menu(window);
        this->_init = true;
    }

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            clickable_system(this->_world, Vector2i{sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y},
                current_screen, client, volume);
        }
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::P) {
            current_screen = SceneScreen::LOBBY;
        } else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::O) {
            current_screen = SceneScreen::OPTION;
        } else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Q) {
            window.close();
        }
        if (event.type == sf::Event::Closed || current_screen == SceneScreen::NONE)
            window.close();
    }

    window.clear(sf::Color::Black);
    drawable_system(this->_world, window);
    window.display();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

void MenuScene::init_menu(sf::RenderWindow &window)
{
    // background
    _world.create_drawable_object("assets/background/menu.jpg", Vector4i{0, 0, 1920, 1080},
        Vector4i{255, 255, 255, 255}, Vector2f{1.0, 1.0}, Vector2f{0, 0});

    // title
    _world.create_text("AIR-TYPE", "assets/font/EMINOR-BlackItalic.ttf", 70,
        Vector2f{static_cast<float>(window.getSize().x / 2 - 140), 0.0f});

    // Play button
    Vector2f pos = {static_cast<float>(window.getSize().x / 2 - ((657 * 0.4) / 2)), 250};
    _world.create_button("assets/background/bg-boutton.png", Vector4i{41, 28, 657, 284}, Vector4i{255, 255, 255, 255},
        Vector2f{0.4, 0.4}, pos, &go_to_lobby);
    _world.create_text("PLAY", "assets/font/EMINOR-BlackItalic.ttf", 40,
        Vector2f{static_cast<float>(window.getSize().x / 2 - 40), 290});

    // Option button
    pos = {static_cast<float>(window.getSize().x / 2 - ((657 * 0.4) / 2)), 400};
    _world.create_button("assets/background/bg-boutton.png", Vector4i{41, 28, 657, 284}, Vector4i{255, 255, 255, 255},
        Vector2f{0.4, 0.4}, pos, &go_to_option);
    _world.create_text("OPTION", "assets/font/EMINOR-BlackItalic.ttf", 40,
        Vector2f{static_cast<float>(window.getSize().x / 2 - 50), 440});

    // Quit button
    pos = {static_cast<float>(window.getSize().x / 2 - ((657 * 0.4) / 2)), 550};
    _world.create_button("assets/background/bg-boutton.png", Vector4i{41, 28, 657, 284}, Vector4i{255, 255, 255, 255},
        Vector2f{0.4, 0.4}, pos, &quit_callback);
    _world.create_text("QUIT", "assets/font/EMINOR-BlackItalic.ttf", 40,
        Vector2f{static_cast<float>(window.getSize().x / 2 - 40), 590});
}
