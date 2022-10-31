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

MenuScene::MenuScene(): _world(true)
{
    _world.create_player(GameObject::PLAYER, Vector2f{0, 0}, Vector2i{1, 1}, 0.2, 0);
}

SceneScreen MenuScene::run(sf::RenderWindow &window)
{
    sf::Event event;

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
    return (SceneScreen::MENU);
}