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

void go_to_lobby(World &world, SceneScreen &actual_screen, NetworkClient &client)
{
    (void)world;
    (void)client;
    actual_screen = SceneScreen::LOBBY;
}

void go_to_menu(World &world, SceneScreen &actual_screen, NetworkClient &client)
{
    (void)world;
    (void)client;
    actual_screen = SceneScreen::MENU;
}

void go_to_game(World &world, SceneScreen &actual_screen, NetworkClient &client)
{
    (void)world;
    (void)client;
    actual_screen = SceneScreen::GAME;
}

void go_to_option(World &world, SceneScreen &actual_screen, NetworkClient &client)
{
    (void)world;
    (void)client;
    actual_screen = SceneScreen::OPTION;
}

void quit_callback(World &world, SceneScreen &actual_screen, NetworkClient &client)
{
    (void)world;
    (void)client;
    actual_screen = SceneScreen::NONE;
}

void launch_game(World &world, SceneScreen &actual_screen, NetworkClient &client)
{
    (void)world;
    Message<GameMessage> msg;
    msg.header.id = GameMessage::C2S_START_GAME;
    msg << "start";
    client.send(msg);
    actual_screen = SceneScreen::GAME;
}

void select_armored_ship(World &world, SceneScreen &actual_screen, NetworkClient &client)
{
    (void)world;
    (void)actual_screen;
    Message<GameMessage> msg;
    msg.header.id = GameMessage::C2S_SELECT_SHIP;
    GameObject obj = GameObject::ARMORED;
    msg << obj;
    client.send(msg);
}

void select_damage_ship(World &world, SceneScreen &actual_screen, NetworkClient &client)
{
    (void)world;
    (void)actual_screen;
    Message<GameMessage> msg;
    msg.header.id = GameMessage::C2S_SELECT_SHIP;
    GameObject obj = GameObject::DAMAGE;
    msg << obj;
    client.send(msg);
}

void select_engineer_ship(World &world, SceneScreen &actual_screen, NetworkClient &client)
{
    (void)world;
    (void)actual_screen;
    Message<GameMessage> msg;
    msg.header.id = GameMessage::C2S_SELECT_SHIP;
    GameObject obj = GameObject::ENGINEER;
    msg << obj;
    client.send(msg);
}

void select_sniper_ship(World &world, SceneScreen &actual_screen, NetworkClient &client)
{
    (void)world;
    (void)actual_screen;
    Message<GameMessage> msg;
    msg.header.id = GameMessage::C2S_SELECT_SHIP;
    GameObject obj = GameObject::SNIPER;
    msg << obj;
    client.send(msg);
}