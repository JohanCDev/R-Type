/**
 * @file SoundEffectComponent.hpp
 * @author Louis Maestre (louis.maestre@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-10-18
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <SFML/Audio.hpp>
#include <chrono>
#include <string>

/**
 * @brief Add sound effect for entities
 *
 */
struct SoundEffectComponent {
    /**
     * @brief Path to the sound
     *
     */
    std::string soundEffect;

    /**
     * @brief Is the entity alive
     *
     */
    bool _alive;

    /**
     * @brief Construct a new Sound Effect Component object
     *
     * @param sound Sound to use
     * @param alive Is the entity alive
     */
    SoundEffectComponent(const std::string &sound, bool alive = true) : soundEffect(sound), _alive(alive){};
};