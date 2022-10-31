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
     * @param client
     */
    World(bool client);

    /**
     * @brief Construct a new World object
     *
     */
    World();

    /**
     * @brief Destroy the World object
     *
     */
    ~World();

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
     * @param pos
     * @param speed
     * @param refresh_time
     * @param elapsed_time
     */
    size_t create_laser(
        GameObject object, GameTeam team, Vector2f pos, Vector2i speed, float refresh_time, float elapsed_time);

    /**
     * @brief Create a player entity
     *
     * @param object
     * @param pos
     * @param speed
     * @param refresh_time
     */
    size_t create_player(GameObject object, Vector2f pos, Vector2i speed, float refresh_time, float elapsed_time);

    /**
     * @brief Create a enemy entity
     *
     * @param object
     * @param pos
     * @param speed
     * @param refresh_time
     * @param elapsed_time
     */
    size_t create_enemy(GameObject object, Vector2f pos, Vector2i speed, float refresh_time, float elapsed_time);

    void register_all_drawable_object();

    registry &getRegistry();
    ResourcesManager &getResourcesManager();
    sf::Clock &getClock();
    Vector2i &getDirection();
    void setDirection(Vector2i direction);

  private:
    registry _r;
    ResourcesManager _manager;
    sf::Clock _clock;
    std::map<GameObject, DrawableComponent> _drawMap;
    Vector2i _player_direction;
};
