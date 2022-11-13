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

void GameScene::run(NetworkClient &client, sf::RenderWindow &window, SceneScreen &current_screen, float &volume)
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
        if (this->_option == true && event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Down)
            down_sound(_world, current_screen, client, volume);
        if (this->_option == true && event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Up)
            up_sound(_world, current_screen, client, volume);
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            if (clickable_system(this->_world, Vector2i{sf::Mouse::getPosition().x, sf::Mouse::getPosition().y},
                    current_screen, client, volume)
                == 1)
                continue;
        }
        if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)) {
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

/**
 * @brief Compare two colors
 *
 * @param first_color First color to compare
 * @param second_color Second color to compare
 *
 * @return true if they are the same
 */
bool compare_color(Vector4i first_color, Vector4i second_color)
{
    if (first_color.x == second_color.x && first_color.y == second_color.y && first_color.x_size == second_color.x_size
        && first_color.y_size == second_color.y_size) {
        return (true);
    }
    return (false);
}

/**
 * @brief Display options
 *
 * @param display Has to display it ?
 */
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
        Vector4i{255, 255, 255, 0}, Vector2f{1.0, 1.0},
        Vector2f{(float)window.getSize().x / 2.0f - 537.0f, (float)window.getSize().y / 2.0f - 201.0f});
    _world.create_button("assets/Button/button_less_volume.png", Vector4i{0, 0, 319, 319}, Vector4i{255, 255, 255, 0},
        Vector2f{0.5, 0.5},
        Vector2f{(float)window.getSize().x / 2.0f - 300.0f, (float)window.getSize().y / 2.0f - 50.0f}, &down_sound);
    _world.create_drawable_object("assets/Button/button_volume.png", Vector4i{0, 0, 319, 319},
        Vector4i{255, 255, 255, 0}, Vector2f{0.5, 0.5},
        Vector2f{(float)window.getSize().x / 2.0f - 75.0f, (float)window.getSize().y / 2.0f - 50.0f});
    _world.create_button("assets/Button/button_more_volume.png", Vector4i{0, 0, 319, 319}, Vector4i{255, 255, 255, 0},
        Vector2f{0.5, 0.5},
        Vector2f{(float)window.getSize().x / 2.0f + 150.0f, (float)window.getSize().y / 2.0f - 50.0f}, &up_sound);
}
