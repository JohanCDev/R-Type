/**
 * @file main.cpp
 * @author Cédric Corge (cedric.corge@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-10-16
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <SFML/Graphics.hpp>

#include "../ECS/World.hpp"

int main(void)
{
    World world(sf::VideoMode(800, 600), "My window");

    std::srand(std::time(NULL));

    world.register_all_component();
    world.register_all_system();
    world.register_all_assets();
    // run the program as long as the window is open
    
    world.create_player("assets/r-typesheet5.gif", Vector4{375, 6, 21, 24}, 2.0, 2.0, 20, 20, 3, 5, 5, 0.2, KeyboardInput::Up, KeyboardInput::Down, KeyboardInput::Right, KeyboardInput::Left, MouseInput::Left_click);
    while (world.getWindow().isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (world.getWindow().pollEvent(event)) {
            // "close requested" event: we close the window
            if (controllable_system(world, event) == 1)
                continue;
            if (event.type == sf::Event::Closed)
                world.getWindow().close();
        }
        world.getWindow().clear(sf::Color::Black);
        for (auto &system: world.getRegistry().get_systems()) {
            system(world);
        }
        world.getWindow().display();
    }
    return (0);
}
