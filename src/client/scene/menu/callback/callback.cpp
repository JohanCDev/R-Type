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

#include "../../Scene.hpp"

void play_callback(World &world, SceneScreen &actual_screen)
{
    (void)world;
    actual_screen = SceneScreen::LOBBY;
}

void quit_callback(World &world, SceneScreen &actual_screen)
{
    (void)world;
    actual_screen = SceneScreen::NONE;
}