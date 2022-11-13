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

/**
 * @brief Go to lobby screen
 *
 * @param world World to act on
 * @param current_screen current screen that will be moidified
 * @param client Class containing information on client's network
 * @param volume Volume of the game
 */
void go_to_lobby(World &world, SceneScreen &current_screen, NetworkClient &client, float &volume);

/**
 * @brief Go to menu screen
 *
 * @param world World to act on
 * @param current_screen current screen that will be moidified
 * @param client Class containing information on client's network
 * @param volume Volume of the game
 */
void go_to_menu(World &world, SceneScreen &current_screen, NetworkClient &client, float &volume);

/**
 * @brief Go to game screen
 *
 * @param world World to act on
 * @param current_screen current screen that will be moidified
 * @param client Class containing information on client's network
 * @param volume Volume of the game
 */
void go_to_game(World &world, SceneScreen &current_screen, NetworkClient &client, float &volume);

/**
 * @brief Go to option screen
 *
 * @param world World to act on
 * @param current_screen current screen that will be moidified
 * @param client Class containing information on client's network
 * @param volume Volume of the game
 */
void go_to_option(World &world, SceneScreen &current_screen, NetworkClient &client, float &volume);

/**
 * @brief Quit the callback map
 *
 * @param world World to act on
 * @param current_screen current screen that will be moidified
 * @param client Class containing information on client's network
 * @param volume Volume of the game
 */
void quit_callback(World &world, SceneScreen &current_screen, NetworkClient &client, float &volume);

/**
 * @brief Launch the game
 *
 * @param world World to act on
 * @param current_screen current screen that will be moidified
 * @param client Class containing information on client's network
 * @param volume Volume of the game
 */
void launch_game(World &world, SceneScreen &current_screen, NetworkClient &client, float &volume);

/**
 * @brief Select the sniper ship
 *
 * @param world World to act on
 * @param current_screen current screen that will be moidified
 * @param client Class containing information on client's network
 * @param volume Volume of the game
 */
void select_sniper_ship(World &world, SceneScreen &current_screen, NetworkClient &client, float &volume);

/**
 * @brief Select the damage ship
 *
 * @param world World to act on
 * @param current_screen current screen that will be moidified
 * @param client Class containing information on client's network
 * @param volume Volume of the game
 */
void select_damage_ship(World &world, SceneScreen &current_screen, NetworkClient &client, float &volume);

/**
 * @brief Select the engineer ship
 *
 * @param world World to act on
 * @param current_screen current screen that will be moidified
 * @param client Class containing information on client's network
 * @param volume Volume of the game
 */
void select_engineer_ship(World &world, SceneScreen &current_screen, NetworkClient &client, float &volume);

/**
 * @brief Select the armored ship
 *
 * @param world World to act on
 * @param current_screen current screen that will be moidified
 * @param client Class containing information on client's network
 * @param volume Volume of the game
 */
void select_armored_ship(World &world, SceneScreen &current_screen, NetworkClient &client, float &volume);

/**
 * @brief increase the sound volume
 *
 * @param world World to act on
 * @param current_screen current screen that will be moidified
 * @param client Class containing information on client's network
 * @param volume Volume of the game
 */
void up_sound(World &world, SceneScreen &current_screen, NetworkClient &client, float &volume);

/**
 * @brief decrease the sound volume
 *
 * @param world World to act on
 * @param current_screen current screen that will be moidified
 * @param client Class containing information on client's network
 * @param volume Volume of the game
 */
void down_sound(World &world, SceneScreen &current_screen, NetworkClient &client, float &volume);