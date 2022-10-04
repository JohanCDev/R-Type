/**
 * @file main.cpp
 * @author Johan Chrillesen (johan.chrillesen@epitech.eu)
 * @brief Main file of the client
 * @version 0.1
 * @date 2022-09-20
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <SFML/Window.hpp>

/**
 * @brief main function of the client
 *
 * @return 0 if success or 84 if error
 */
int main()
{
    sf::Window window(sf::VideoMode(800, 600), "My window");

    // run the program as long as the window is open
    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

    return 0;
}