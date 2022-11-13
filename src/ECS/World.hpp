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

#include <SFML/Audio.hpp>
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
     * @brief Register assets for option scene
     *
     */
    void register_option_assets();

    /**
     * @brief Register assets for menu scene
     *
     */
    void register_menu_assets();

    /**
     * @brief Register assets for game scene
     *
     */
    void register_game_assets();

    /**
     * @brief Register assets for lobby scene
     *
     */
    void register_lobby_assets();

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
     * @brief Create a laser entity in the enemy team
     *
     * @param object type of the object
     * @param team Team of the laser
     * @param pos base pos of the laser as a Vector2f. ex: {150.0, 120.0}
     * @param speed base speed of the laser as a Vector2i. ex: {0, 0}
     * @param refresh_time time before the laser is refreshed
     *
     * @returns id of the laser
     */
    size_t create_laser_enemy(GameObject object, GameTeam team, Vector2f pos, Vector2i speed, float refresh_time);

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
     * @brief Create a bonus object
     *
     * @param object type of the object
     * @param pos base pos of the enemy as a Vector2f. ex: {150.0, 120.0}
     * @param speed base speed of the enemy as a Vector2i. ex: {0, 0}
     * @param refresh_time time before the laser is refreshed
     * @param enumBonus enumeration of bonus stats
     * @return size_t
     */
    size_t create_bonus(GameObject object, Vector2f pos, Vector2i speed, float refresh_time, Bonus enumBonus);
    /**
     * @brief Create a drawable object
     *
     * @param asset_path Path to the asset
     * @param rect Display rect of object
     * @param color Color of the rectangle
     * @param scale Scale of the asset
     * @param pos Pos of the object
     * @param speed Speed of the object
     * @param refresh_time Time before the object is refreshed
     *
     * @returns Negative value if there is an error
     */
    size_t create_drawable_object(std::string asset_path, Vector4i rect, Vector4i color, Vector2f scale, Vector2f pos,
        Vector2i speed = {0, 0}, float refresh_time = 0);

    /**
     * @brief Create a text object
     *
     * @param text Text to display
     * @param font Font to use
     * @param size Font Size
     * @param pos Position of the text
     *
     * @returns Negative value if there is an error
     */
    size_t create_text(std::string text, std::string font, int size, Vector2f pos);

    /**
     * @brief Create a button object
     *
     * @param asset asset of the button
     * @param rect Size of the button
     * @param color Color of the button
     * @param scale Scale of the button
     * @param pos Pos of the button
     * @param callback Function to call on click
     * @return ID of the button
     */
    size_t create_button(std::string asset, Vector4i rect, Vector4i color, Vector2f scale, Vector2f pos,
        std::function<void(World &, SceneScreen &, NetworkClient &, float &)> callback);

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
     * @brief Get the Music object
     *
     * @return Reference to the music object
     */
    sf::Music &getMusic();

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

    /**
     * @brief State of the game
     *
     */
    GameState state;

    /**
     * @brief Map containing all players' ships
     *
     */
    std::map<std::size_t, GameObject> player_ships;

    /**
     * @brief Create a border entities object that will destroy objects passing through
     *
     */
    void create_border_entities();

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
     * @brief Music of the game
     *
     */
    sf::Music _music;

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
