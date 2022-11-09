/**
 * @file World.hpp
 * @author Cédric Corge (cedric.corge@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-10-17
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "Registry.hpp"
#include "ResourcesManager.hpp"

#include "Systems/AllSystem.hpp"

#include <SFML/Graphics.hpp>
#include <map>

/**
 * @brief Store entity and usefull function
 *
 */
class World {
  public:
    /**
     * @brief Construct a new World object
     *
     * @param mode
     * @param name
     */
    World(sf::VideoMode mode, std::string name);
    World(void);

    /**
     * @brief Destroy the World object
     *
     */
    ~World();

    /**
     * @brief Register all existing components
     *
     */
    void register_all_component();

    /**
     * @brief register all existing systems
     *
     */
    void register_all_system();

    /**
     * @brief register all assets of the game
     *
     */
    void register_all_assets();

    /**
     * @brief Create a laser entity
     *
     * @param object type of the object
     * @param team Team of the laser
     * @param pos base pos of the laser as a Vector2f. ex: {150.0, 120.0}
     * @param speed base speed of the laser as a Vector2i. ex: {0, 0}
     * @param refresh_time time before the laser is refreshed
     *
     * @returns id of the laser
     */
    size_t create_laser(GameObject object, GameTeam team, Vector2f pos, Vector2i speed, float refresh_time);

    /**
     * @brief Create a player entity
     *
     * @param object type of the object
     * @param pos base pos of the player as a Vector2f. ex: {150.0, 120.0}
     * @param speed base speed of the player as a Vector2i. ex: {0, 0}
     * @param refresh_time time before the laser is refreshed
     *
     * @returns id of the player
     */
    size_t create_player(GameObject object, Vector2f pos, Vector2i speed, float refresh_time);

    /**
     * @brief Create a enemy entity
     *
     * @param object type of the object
     * @param pos base pos of the enemy as a Vector2f. ex: {150.0, 120.0}
     * @param speed base speed of the enemy as a Vector2i. ex: {0, 0}
     * @param health base health of the enemy as an unsigned int
     * @param refresh_time time before the laser is refreshed
     *
     * @returns id of the enemy
     */
    size_t create_enemy(GameObject object, Vector2f pos, Vector2i speed, size_t health, float refresh_time);

    /**
     * @brief Create a skills entity
     *
     * @param pos base pos of the skill object as a Vector2f. ex: {150.0, 120.0}
     */
    void create_skills(Vector2f pos);

    /**
     * @brief settings button
     *
     * @param pos base pos of the settings button as a Vector2f. ex: {150.0, 120.0}
     */
    void create_settings(Vector2f pos);

    /**
     * @brief settings button
     *
     * @param life percentage of life remaining
     */
    void create_healthbar(float life);

    /**
     * @brief Registers all drawable objects
     *
     */
    void register_all_drawable_object();

    /**
     * @brief Get the Registry object
     *
     * @return Reference to the registry
     */
    registry &getRegistry();

    /**
     * @brief Get the Resources Manager object
     *
     * @return Reference to the resources manager
     */
    ResourcesManager &getResourcesManager();

    /**
     * @brief Get the Window object
     *
     * @return Reference to the renderWindow object
     */
    sf::RenderWindow &getWindow();

    /**
     * @brief Get the Clock object
     *
     * @return Reference to the clock object
     */
    sf::Clock &getClock();

    /**
     * @brief Get the Direction object
     *
     * @return Reference to the direction
     */
    Vector2i &getDirection();

    /**
     * @brief Set the Direction object
     *
     * @param direction new direction as a Vector2i. ex: {0, 0}
     */
    void setDirection(Vector2i direction);

  private:
    /**
     * @brief Contains the registry object
     *
     */
    registry _r;

    /**
     * @brief Contains the resources manager object
     *
     */
    ResourcesManager _manager;

    /**
     * @brief SFML window used to draw textures
     *
     */
    sf::RenderWindow _window;

    /**
     * @brief Clock of the game
     *
     */
    sf::Clock _clock;

    /**
     * @brief Map containing all the drawable components
     *
     * The key is the type of the GameObject, the value being the drawableComponent to display
     *
     */
    std::map<GameObject, DrawableComponent> _drawMap;

    /**
     * @brief Player actual direction
     *
     */
    Vector2i _player_direction;
};
