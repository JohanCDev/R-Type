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

#include "EndGame.hpp"

EndGameScene::EndGameScene() : _world(true), _init(false)
{
}

void EndGameScene::run(NetworkClient &client, sf::RenderWindow &window, SceneScreen &current_screen, float &volume)
{
    (void)client;
    sf::Event event;

    if (this->_init == false) {
        this->_world.register_end_game_assets();
        this->init_end_game(window);
        this->_init = true;
    }

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            clickable_system(this->_world, Vector2i{sf::Mouse::getPosition().x, sf::Mouse::getPosition().y},
                current_screen, client, volume);
        }
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::M) {
            go_to_menu(_world, current_screen, client, volume);
        }
        if (event.type == sf::Event::Closed || current_screen == SceneScreen::NONE)
            window.close();
    }

    window.clear(sf::Color::Black);
    drawable_system(this->_world, window);
    window.display();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

void EndGameScene::init_end_game(sf::RenderWindow &window)
{
    this->_world.create_text(
        "Game Over", "assets/font/EMINOR-BlackItalic.ttf", 50, Vector2f{(float)window.getSize().x / 2.0f - 112.5f, 50});

    Vector2f pos;
    pos = {static_cast<float>(window.getSize().x / 2 - ((657 * 0.4) / 2)), 250};
    _world.create_button("assets/background/bg-boutton.png", Vector4i{41, 28, 657, 284}, Vector4i{255, 255, 255, 255},
        Vector2f{0.4, 0.4}, pos, &go_to_menu);
    _world.create_text("MENU", "assets/font/EMINOR-BlackItalic.ttf", 40,
        Vector2f{static_cast<float>(window.getSize().x / 2 - 40), 290});
}
