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
#include "../server/GameStates.hpp"

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
     * @param object
     * @param team
     * @param pos
     * @param speed
     * @param refresh_time
     */
    size_t create_laser(GameObject object, GameTeam team, Vector2f pos, Vector2i speed, float refresh_time);

    /**
     * @brief Create a player entity
     *
     * @param object
     * @param pos
     * @param speed
     * @param refresh_time
     */
    size_t create_player(GameObject object, Vector2f pos, Vector2i speed, float refresh_time);

    /**
     * @brief Create a enemy entity
     *
     * @param object
     * @param pos
     * @param speed
     * @param health
     * @param refresh_time
     */
    size_t create_enemy(GameObject object, Vector2f pos, Vector2i speed, size_t health, float refresh_time);

    /**
     * @brief Create a skills entity
     *
     * @param pos
     */
    void create_skills(Vector2f pos);

    /**
     * @brief settings button
     *
     * @param pos
     */
    void create_settings(Vector2f pos);

    /**
     * @brief settings button
     *
     * @param life percentage of life remaining
     * @param pos
     */
    void create_healthbar(float life);

    void register_all_drawable_object();

    registry &getRegistry();
    ResourcesManager &getResourcesManager();
    sf::RenderWindow &getWindow();
    sf::Clock &getClock();
    Vector2i &getDirection();
    void setDirection(Vector2i direction);

    GameState state;
    std::map<std::size_t, GameObject> player_ships;

  private:
    registry _r;
    ResourcesManager _manager;
    sf::RenderWindow _window;
    sf::Clock _clock;
    std::map<GameObject, DrawableComponent> _drawMap;
    Vector2i _player_direction;
};
