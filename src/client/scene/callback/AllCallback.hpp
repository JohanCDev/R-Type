/**
 * @file AllCallback.hpp
 * @author Cédric Corge (cedric.corge@epitech.eu)
 * @brief 
 * @version 0.1
 * @date 2022-11-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

void go_to_lobby(World &world, SceneScreen &actual_screen, NetworkClient &client);
void go_to_menu(World &world, SceneScreen &actual_screen, NetworkClient &client);
void go_to_game(World &world, SceneScreen &actual_screen, NetworkClient &client);
void go_to_option(World &world, SceneScreen &actual_screen, NetworkClient &client);
void quit_callback(World &world, SceneScreen &actual_screen, NetworkClient &client);
void launch_game(World &world, SceneScreen &actual_screen, NetworkClient &client);
void select_sniper_ship(World &world, SceneScreen &actual_screen, NetworkClient &client);
void select_damage_ship(World &world, SceneScreen &actual_screen, NetworkClient &client);
void select_engineer_ship(World &world, SceneScreen &actual_screen, NetworkClient &client);
void select_armored_ship(World &world, SceneScreen &actual_screen, NetworkClient &client);