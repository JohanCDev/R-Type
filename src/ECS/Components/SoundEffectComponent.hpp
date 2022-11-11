/**
 * @file MusicComponent.hpp
 * @author Louis Maestre (louis.maestre@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-10-18
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <string>
#include <chrono>

/**
 * @brief Add sound effect for entities
 * 
 */
struct SoundEffectComponent {
    std::string soundEffect;

    /**
     * @brief Construct a new Sound Effect Component object
     *
     * @param soundEffect string of sound effect
     */
    SoundEffectComponent(std::string sound) : soundEffect(sound) {};
};