/**
 * @file AllSystem.hpp
 * @author Cédric Corge (cedric.corge@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-10-17
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "../../client/client.hpp"
#include "../../server/game.hpp"
#include "../../server/server.hpp"
#include "../World.hpp"

/**
 * @brief Scene screen
 *
 */
enum class SceneScreen : uint32_t;
/**
 * @brief Draw all drawables entities
 *
 * @param world The world
 * @param window The window
 * @return negative value if there is an error
 */
int drawable_system(World &world, sf::RenderWindow &window);

/**
 * @brief Update all controllable entities
 *
 * @param world The world
 * @param event Events received
 * @return negative value if there is an error
 */
int controllable_system(World &world, sf::Event event);

/**
 * @brief Check collision between entities if they have a collider
 *
 * @param world The world
 * @param server The server
 * @return negative value if there is an error
 */
int shooting_system(World &world, NetworkServer &server);

/**
 * @brief Call the AI function of each type of entities
 *
 * @param world The world
 * @param server The server
 * @return negative value if there is an error
 */
int ia_system(World &world, NetworkServer &server);

/**
 * @brief Move all movable entities
 *
 * @param world The world
 * @return negative value if there is an error
 */
int velocity_system(World &world);

/**
 * @brief Start a wave if needed
 *
 * @param world The world
 * @param server The server
 * @param waves Current wave
 * @return negative value if there is an error
 */
int wave_system(World &world, NetworkServer &server, waves_t &waves);

/**
 * @brief Bonus spawn if ennemy die
 *
 * @param world The world
 * @param server The server
 * @param bonus_stat stat bonus for player
 * @return
 */
int bonus_system(World &world, NetworkServer &server, bonus_t &bonus_stat);

/**
 * @brief check collision between two entities
 *
 * @param manager Resources manager
 * @param sprite Sprite to check collision
 * @param position Position of the sprite
 * @param drawable drawable component of drawable
 * @return 1 if there is a collision
 */
int check_collision(ResourcesManager &manager, sf::Sprite sprite, std::optional<PositionComponent> &position,
    std::optional<DrawableComponent> &drawable);

/**
 * @brief Collide all entities
 *
 * @param world The world
 * @param server The server
 * @return negative value if there is an error
 */
int collide_system(World &world, NetworkServer &server);

/**
 * @brief Lobby system
 *
 * @param world The world
 * @param server The server
 *
 * @return negative value if there is an error
 */
int lobby_system(World &world, NetworkServer &server);

/**
 * @brief Clickable system
 *
 * @param world The world
 * @param click_pos pos of the click
 * @param current_screen current screen
 * @param client client struct
 * @param volume volume
 * @return negative value if there is an error
 */
int clickable_system(
    World &world, Vector2i click_pos, SceneScreen &current_screen, NetworkClient &client, float &volume);

/**
 * @brief Sends the locations of each entity to clients
 *
 * @param world world to act on
 * @param server Server with all the informations
 *
 * @returns Negative value if there is an error
 */
int refresh_system(World &world, NetworkServer &server);

/**
 * @brief Creates a music
 *
 * @param world world to act on
 * @param music_filepath filepath to music
 * @param volume volume of the music
 * @return Negative value in case of error
 */
int music_system(World &world, const std::string &music_filepath, float &volume);

/**
 * @brief Destroy entities out of screen
 *
 * @param world
 * @param server
 */
void destroy_outdated_entities(World &world, NetworkServer &server);
