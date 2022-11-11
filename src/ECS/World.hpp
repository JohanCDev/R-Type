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

#include <SFML/Graphics.hpp>
#include <map>
#include "../server/GameStates.hpp"
#include "Registry.hpp"
#include "ResourcesManager.hpp"
#include "Systems/AllSystem.hpp"

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
     * @brief display a healthbar at the top of the window
     *
     * @param index Index of the player
     * @param life Percentage of life remaining
     * @param windowSize Size of the window
     */
    void create_healthbar(int index, float life, Vector2f windowSize);

    /**
     * @brief Create a drawable object
     *
     * @param asset_path
     * @param rect
     * @param color
     * @param scale
     * @param pos
     * @param speed
     * @param refresh_time
     * @param elapsed_time
     *
     */
    size_t create_drawable_object(std::string asset_path, Vector4i rect, Vector4i color, Vector2f scale, Vector2f pos,
        Vector2i speed = {0, 0}, float refresh_time = 0, float elapsed_time = 0);

    /**
     * @brief Create a text object
     *
     * @param text
     * @param font
     * @param size
     * @param pos
     *
     */
    size_t create_text(std::string text, std::string font, int size, Vector2f pos);

    /**
     * @brief Create a button object
     *
     * @param asset
     * @param rect
     * @param scale
     * @param pos
     * @param callback
     * @return size_t
     */
    size_t create_button(std::string asset, Vector4i rect, Vector2f scale, Vector2f pos,
        std::function<void(World &, SceneScreen &, NetworkClient &)> callback);

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
    sf::Clock _clock;
    std::map<GameObject, DrawableComponent> _drawMap;
    Vector2i _player_direction;
};
