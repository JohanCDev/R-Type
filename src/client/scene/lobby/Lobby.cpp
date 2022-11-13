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

LobbyScene::LobbyScene() : _world(true), _connected(false), _init(false)
{
}

/**
 * @brief Light Button to play
 *
 * @param world World to act on
 */
void light_button(World &world)
{
    auto &drawables = world.getRegistry().get_components<DrawableComponent>();

    for (auto &drawable : drawables) {
        if (drawable && drawable.has_value()) {
            if (drawable->path == "assets/background/bg-boutton.png")
                drawable->color = {255, 255, 255, 255};
        }
    }
}

/**
 * @brief Shadow play button
 *
 * @param world World to act on
 */
void shadow_button(World &world)
{
    auto &drawables = world.getRegistry().get_components<DrawableComponent>();

    for (auto &drawable : drawables) {
        if (drawable && drawable.has_value()) {
            if (drawable->path == "assets/background/bg-boutton.png")
                drawable->color = {93, 93, 93, 255};
        }
    }
}

void LobbyScene::run(NetworkClient &client, sf::RenderWindow &window, SceneScreen &current_screen, float &volume)
{
    Message<GameMessage> msg;
    Message<GameMessage> hiMsg;
    hiMsg.header.id = GameMessage::C2S_JOIN;
    hiMsg << "join";

    (void)client;
    sf::Event event;

    if (_connected == false) {
        client.send(hiMsg);
        _connected = true;
    }

    if (this->_init == false) {
        this->_world.register_lobby_assets();
        this->init_lobby(window);
        this->_init = true;
    }

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::P) {
            launch_game(_world, current_screen, client, volume);
        } else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Num1) {
            select_armored_ship(_world, current_screen, client, volume);
        } else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Num2) {
            select_damage_ship(_world, current_screen, client, volume);
        } else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Num3) {
            select_engineer_ship(_world, current_screen, client, volume);
        } else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Num4) {
            select_sniper_ship(_world, current_screen, client, volume);
        }
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            clickable_system(this->_world, Vector2i{sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y},
                current_screen, client, volume);
        }
    }

    while (client.HasMessages()) {
        msg = client.PopMessage();
        client.processMessage(msg, _world, window, current_screen);
        if (current_screen != SceneScreen::LOBBY)
            return;
    }

    if (client.get_launch_game() == true) {
        current_screen = SceneScreen::GAME;
        client.set_launch_game(false);
    }
    update_player_number(client);
    window.clear(sf::Color::Black);
    drawable_system(this->_world, window);
    window.display();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

void LobbyScene::update_player_number(NetworkClient &client)
{
    auto &texts = _world.getRegistry().get_components<TextComponent>();

    for (auto &text : texts) {
        if (text && text.has_value()) {
            if (text->text.substr(0, 7) == "PLAYER:") {
                std::string new_string = "PLAYER: ";
                text->text = new_string + std::to_string(client.get_nb_players()) + "/4";
            }
        }
    }
}

void LobbyScene::init_lobby(sf::RenderWindow &window)
{
    Vector2f pos = {(float)window.getSize().x / 2 - 367.5f, 200.0};
    _world.create_text("CHOOSE YOUR SPACESHIP", "assets/font/EMINOR-BlackItalic.ttf", 70, pos);
    pos = {(float)window.getSize().x - 350.0f, 100.0f};
    _world.create_text("PLAYER: 0/4", "assets/font/EMINOR-BlackItalic.ttf", 50, pos);
    _world.create_drawable_object("assets/background/lobby.png", Vector4i{0, 0, 1056, 672},
        Vector4i{255, 255, 255, 255}, Vector2f{1.9, 1.6}, Vector2f{0, 0});

    pos = {164, (float)window.getSize().y / 2};
    _world.create_button("assets/SpaceShip/ship_armored_spritesheet.png", Vector4i{0, 0, 128, 128},
        Vector4i{255, 255, 255, 255}, Vector2f{2.0, 2.0}, pos, &select_armored_ship);
    pos = {600, (float)window.getSize().y / 2};
    _world.create_button("assets/SpaceShip/ship_damage_spritesheet.png", Vector4i{0, 0, 128, 128},
        Vector4i{255, 255, 255, 255}, Vector2f{2.0, 2.0}, pos, &select_damage_ship);
    pos = {1000, (float)window.getSize().y / 2};
    _world.create_button("assets/SpaceShip/ship_engineer_spritesheet.png", Vector4i{0, 0, 128, 128},
        Vector4i{255, 255, 255, 255}, Vector2f{2.0, 2.0}, pos, &select_engineer_ship);
    pos = {1500, (float)window.getSize().y / 2};
    _world.create_button("assets/SpaceShip/ship_sniper_spritesheet.png", Vector4i{0, 0, 128, 128},
        Vector4i{255, 255, 255, 255}, Vector2f{2.0, 2.0}, pos, &select_sniper_ship);

    pos = {(float)window.getSize().x / 2 - 131.4f, (float)window.getSize().y - 124.0f};
    _world.create_button("assets/background/bg-boutton.png", Vector4i{41, 28, 657, 284}, Vector4i{255, 255, 255, 255},
        Vector2f{0.4, 0.4}, pos, &launch_game);
    _world.create_text("PLAY", "assets/font/EMINOR-BlackItalic.ttf", 40,
        Vector2f{static_cast<float>(window.getSize().x / 2 - 40), pos.y + 40});
}
