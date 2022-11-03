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

void go_to_lobby(World &world, SceneScreen &actual_screen)
{
    (void)world;
    actual_screen = SceneScreen::LOBBY;
}

void go_to_menu(World &world, SceneScreen &actual_screen)
{
    (void)world;
    actual_screen = SceneScreen::MENU;
}

void go_to_game(World &world, SceneScreen &actual_screen)
{
    (void)world;
    actual_screen = SceneScreen::GAME;
}

void go_to_option(World &world, SceneScreen &actual_screen)
{
    (void)world;
    actual_screen = SceneScreen::OPTION;
}

void quit_callback(World &world, SceneScreen &actual_screen)
{
    (void)world;
    actual_screen = SceneScreen::NONE;
}