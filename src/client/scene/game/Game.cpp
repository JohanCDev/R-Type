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

GameScene::GameScene() : _world(true), _init(false), _option(false)
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
        this->_world.register_game_assets();
        this->init_game(window);
        _init = true;
    }

    while (window.pollEvent(event)) {
        handle_movement(_world, client, event);
        if (event.type == sf::Event::Closed) {
            window.close();
            client.send(byeMsg);
        }
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape) {
            this->_option = !this->_option;
            this->display_option(this->_option);
        }
        if ((event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)) {
            client.send(shootMsg);
        }
    }

    while (client.HasMessages()) {
        this->msg = client.PopMessage();
        client.processMessage(this->msg, _world, window, current_screen);
    }
    window.clear(sf::Color::Black);
    update_parallax();
    drawable_system(_world, window);
    velocity_system(_world);
    window.display();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

static std::vector<std::string> parallax_assets_vector{
    "assets/background/bkgd_1.png",
    "assets/background/bkgd_2.png",
};
void GameScene::update_parallax()
{
    auto &drawables = _world.getRegistry().get_components<DrawableComponent>();
    auto &positions = _world.getRegistry().get_components<PositionComponent>();

    for (size_t i = 0; i < drawables.size(); ++i) {
        if (drawables[i] && drawables[i].has_value()) {
            std::vector<std::string>::iterator it =
                std::find(parallax_assets_vector.begin(), parallax_assets_vector.end(), drawables[i]->path);
            if (it != parallax_assets_vector.end()) {
                if (positions[i]->pos.x <= -(drawables[i]->rect.x_size * drawables[i]->scale.x)) {
                    positions[i]->pos.x = (drawables[i]->rect.x_size * drawables[i]->scale.x);
                }
            }
        }
    }
}

bool compare_color(Vector4i first_color, Vector4i second_color)
{
    if (first_color.x == second_color.x && first_color.y == second_color.y && first_color.x_size == second_color.x_size
        && first_color.y_size == second_color.y_size) {
        return (true);
    }
    return (false);
}

void GameScene::display_option(bool display)
{
    auto &drawables = _world.getRegistry().get_components<DrawableComponent>();

    for (size_t i = 0; i < drawables.size(); ++i) {
        if (drawables[i] && drawables[i].has_value()) {
            if (compare_color(drawables[i]->color, Vector4i{255, 255, 255, 0}) == true && display == true) {
                drawables[i]->color = Vector4i{255, 255, 255, 254};
            }
            if (compare_color(drawables[i]->color, Vector4i{255, 255, 255, 254}) == true && display == false) {
                drawables[i]->color = Vector4i{255, 255, 255, 0};
            }
        }
    }
}

void GameScene::init_game(sf::RenderWindow &window)
{
    _world.create_drawable_object("assets/background/bkgd_1.png", Vector4i{0, 0, 1000, 1000},
        Vector4i{255, 255, 255, 255}, Vector2f{2.0, 2.0}, Vector2f{0, 0}, Vector2i{-4, 0}, 0.04f);
    _world.create_drawable_object("assets/background/bkgd_2.png", Vector4i{0, 0, 1000, 1000},
        Vector4i{255, 255, 255, 255}, Vector2f{2.0, 2.0}, Vector2f{0, 0}, Vector2i{-5, 0}, 0.04f);
    _world.create_drawable_object("assets/background/bkgd_1.png", Vector4i{0, 0, 1000, 1000},
        Vector4i{255, 255, 255, 255}, Vector2f{2.0, 2.0}, Vector2f{2000, 0}, Vector2i{-4, 0}, 0.04f);
    _world.create_drawable_object("assets/background/bkgd_2.png", Vector4i{0, 0, 1000, 1000},
        Vector4i{255, 255, 255, 255}, Vector2f{2.0, 2.0}, Vector2f{2000, 0}, Vector2i{-5, 0}, 0.04f);
    _world.create_skills(Vector2f{(float)window.getSize().x, (float)window.getSize().y});
    _world.create_settings(Vector2f{(float)window.getSize().x, (float)window.getSize().y});
    _world.create_healthbar(1);
    _world.create_drawable_object("assets/background/bg-settings.png", Vector4i{0, 0, 1074, 402},
        Vector4i{255, 255, 255, 0}, Vector2f{1.0, 1.0}, Vector2f{0, 0});
}
