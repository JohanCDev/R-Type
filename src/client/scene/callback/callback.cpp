/**
 * @file play_callback.cpp
 * @author Cédric Corge (cedric.corge@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-11-03
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "../Scene.hpp"

void go_to_lobby(World &world, SceneScreen &current_screen, NetworkClient &client)
{
    (void)world;
    (void)client;
    current_screen = SceneScreen::LOBBY;
}

void go_to_menu(World &world, SceneScreen &current_screen, NetworkClient &client)
{
    (void)world;
    (void)client;
    current_screen = SceneScreen::MENU;
}

void go_to_game(World &world, SceneScreen &current_screen, NetworkClient &client)
{
    (void)world;
    (void)client;
    current_screen = SceneScreen::GAME;
}

void go_to_option(World &world, SceneScreen &current_screen, NetworkClient &client)
{
    (void)world;
    (void)client;
    current_screen = SceneScreen::OPTION;
}

void quit_callback(World &world, SceneScreen &current_screen, NetworkClient &client)
{
    (void)world;
    (void)client;
    current_screen = SceneScreen::NONE;
}

void launch_game(World &world, SceneScreen &current_screen, NetworkClient &client)
{
    (void)world;
    if (client.get_players_ready() == false)
        return;
    Message<GameMessage> msg;
    msg.header.id = GameMessage::C2S_START_GAME;
    msg << "start";
    client.send(msg);
    current_screen = SceneScreen::GAME;
}

static std::vector<std::string> asset_vector{"assets/SpaceShip/ship_armored_spritesheet.png",
    "assets/SpaceShip/ship_damage_spritesheet.png", "assets/SpaceShip/ship_engineer_spritesheet.png",
    "assets/SpaceShip/ship_sniper_spritesheet.png"};

void shadow_other_ship(World &world, std::string &except)
{
    auto &drawables = world.getRegistry().get_components<DrawableComponent>();
    for (auto &drawable : drawables) {
        if (drawable && drawable.has_value()) {
            std::vector<std::string>::iterator it = std::find(asset_vector.begin(), asset_vector.end(), drawable->path);
            if (it != asset_vector.end() && drawable->path != except) {
                drawable->color = {93, 93, 93, 255};
            } else if (it != asset_vector.end() && drawable->path == except) {
                drawable->color = {255, 255, 255, 255};
            }
        }
    }
}

void select_armored_ship(World &world, SceneScreen &current_screen, NetworkClient &client)
{
    (void)world;
    (void)current_screen;

    std::string except = "assets/SpaceShip/ship_armored_spritesheet.png";
    shadow_other_ship(world, except);

    Message<GameMessage> msg;
    msg.header.id = GameMessage::C2S_SELECT_SHIP;
    GameObject obj = GameObject::SHIP_ARMORED;
    msg << obj;
    client.send(msg);
}

void select_damage_ship(World &world, SceneScreen &current_screen, NetworkClient &client)
{
    (void)world;
    (void)current_screen;

    std::string except = "assets/SpaceShip/ship_damage_spritesheet.png";
    shadow_other_ship(world, except);

    Message<GameMessage> msg;
    msg.header.id = GameMessage::C2S_SELECT_SHIP;
    GameObject obj = GameObject::SHIP_DAMAGE;
    msg << obj;
    client.send(msg);
}

void select_engineer_ship(World &world, SceneScreen &current_screen, NetworkClient &client)
{
    (void)world;
    (void)current_screen;

    std::string except = "assets/SpaceShip/ship_engineer_spritesheet.png";
    shadow_other_ship(world, except);

    Message<GameMessage> msg;
    msg.header.id = GameMessage::C2S_SELECT_SHIP;
    GameObject obj = GameObject::SHIP_ENGINEER;
    msg << obj;
    client.send(msg);
}

void select_sniper_ship(World &world, SceneScreen &current_screen, NetworkClient &client)
{
    (void)world;
    (void)current_screen;

    std::string except = "assets/SpaceShip/ship_sniper_spritesheet.png";
    shadow_other_ship(world, except);

    Message<GameMessage> msg;
    msg.header.id = GameMessage::C2S_SELECT_SHIP;
    GameObject obj = GameObject::SHIP_SNIPER;
    msg << obj;
    client.send(msg);
}
