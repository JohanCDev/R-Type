/**
 * @file ControllableSystem.cpp
 * @author Cédric Corge (cedric.corge@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-10-16
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>
#include "../Components/AllComponents.hpp"
#include "../Registry.hpp"
#include "../ResourcesManager.hpp"
#include "../World.hpp"

int controllable_system(World &world, sf::Event event)
{
    registry &r = world.getRegistry();
    sparse_array<ControllableComponent> &controllable = r.get_components<ControllableComponent>();
    sparse_array<VelocityComponent> &velocity = r.get_components<VelocityComponent>();
    sparse_array<PositionComponent> &position = r.get_components<PositionComponent>();
    sparse_array<DrawableComponent> &drawable = r.get_components<DrawableComponent>();
    std::size_t index = 0;

    for (auto const &i : controllable) {
        if (i && i.has_value()) {
            if (event.type == sf::Event::KeyPressed && (KeyboardInput)event.key.code == i->up) {
                position[index]->y -= velocity[index]->y;
                return (1);
            }
            if (event.type == sf::Event::KeyPressed && (KeyboardInput)event.key.code == i->down) {
                position[index]->y += velocity[index]->y;
                return (1);
            }
            if (event.type == sf::Event::KeyPressed && (KeyboardInput)event.key.code == i->left) {
                position[index]->x -= velocity[index]->x;
                return (1);
            }
            if (event.type == sf::Event::KeyPressed && (KeyboardInput)event.key.code == i->right) {
                position[index]->x += velocity[index]->x;
                return (1);
            }
            if (event.type == sf::Event::MouseButtonPressed && (MouseInput)event.mouseButton.button == i->shoot) {
                if (!(drawable[index]->rect.x == 0 && drawable[index]->rect.y == 0 && drawable[index]->rect.x_size == 0
                        && drawable[index]->rect.y_size == 0)) {
                    world.create_laser(position[index]->x + (drawable[index]->rect.x_size * drawable[index]->x_scale) + 1,
                        position[index]->y + ((drawable[index]->rect.y_size * drawable[index]->y_scale) / 2), 15, 0,
                        0.04, world.getClock().getElapsedTime().asSeconds());
                } else {
                    world.create_laser(position[index]->x
                            + (world.getRessourcesManager().get_texture(drawable[index]->path).getSize().x * drawable[index]->x_scale) + 1,
                        position[index]->y + ((drawable[index]->rect.y_size * drawable[index]->y_scale) / 2), 15, 0,
                        0.04, world.getClock().getElapsedTime().asSeconds());
                }
            }
        }
        index++;
    }
    return (0);
}
