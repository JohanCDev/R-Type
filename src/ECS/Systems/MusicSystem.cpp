/**
 * @file MusicSystem.cpp
 * @author Johan Chrillesen (johan.chrillesen@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-11-11
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "../Components/AllComponents.hpp"
#include "../World.hpp"

int music_system(World &world, const std::string &music_filepath, float &volume)
{
    if (world.getMusic().openFromFile(music_filepath) == false)
        return -1;
    world.getMusic().setLoop(true);
    world.getMusic().setVolume(volume);
    world.getMusic().play();
    return 0;
}
