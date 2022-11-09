/**
 * @file Option.cpp
 * @author Cédric Corge (cedric.corge@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-11-03
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "Option.hpp"

OptionScene::OptionScene() : _world(true), _init(false)
{
}

void OptionScene::run(NetworkClient &client, sf::RenderWindow &window, SceneScreen &actual_screen)
{
    (void)client;
    sf::Event event;

    if (this->_init == false) {
        this->init_option(window);
        this->_init = true;
    }

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            clickable_system(
                this->_world, Vector2i{sf::Mouse::getPosition().x, sf::Mouse::getPosition().y}, actual_screen, client);
        }
        if (event.type == sf::Event::Closed || actual_screen == SceneScreen::NONE)
            window.close();
    }

    window.clear(sf::Color::Black);
    drawable_system(this->_world, window);
    window.display();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

void OptionScene::init_option(sf::RenderWindow &window)
{
    Vector2f pos = {(float)window.getSize().x / 2 - 105.0f, 150};
    this->_world.create_text("OPTION", "assets/font/EMINOR-BlackItalic.ttf", 70, pos);

    pos = {(float)window.getSize().x + 100, (float)window.getSize().y / 2};
    // this->_world.create_button("assets/background/bg-setting.png", Vector4i{0, 0, 1074, 402}, Vector2f{0.4, 0.6},
    // pos, &up_sound);

    pos = {(float)window.getSize().x / 2 - 80.0f, (float)window.getSize().y - 170};
    this->_world.create_button(
        "assets/Button/home.png", Vector4i{0, 0, 319, 319}, Vector2f{0.5, 0.5}, pos, &go_to_menu);
}
