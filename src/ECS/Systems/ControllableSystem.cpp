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
#include "../Common/Message/Message.hpp"
#include "../Common/Message/MessageType.hpp"

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
                position[index]->pos.y -= velocity[index]->speed.y;
                return (1);
            }
            if (event.type == sf::Event::KeyPressed && (KeyboardInput)event.key.code == i->down) {
                position[index]->pos.y += velocity[index]->speed.y;
                return (1);
            }
            if (event.type == sf::Event::KeyPressed && (KeyboardInput)event.key.code == i->left) {
                position[index]->pos.x -= velocity[index]->speed.x;
                return (1);
            }
            if (event.type == sf::Event::KeyPressed && (KeyboardInput)event.key.code == i->right) {
                position[index]->pos.x += velocity[index]->speed.x;
                return (1);
            }
            if (event.type == sf::Event::MouseButtonPressed && (MouseInput)event.mouseButton.button == i->shoot) {
                if (!(drawable[index]->rect.x == 0 && drawable[index]->rect.y == 0 && drawable[index]->rect.x_size == 0
                        && drawable[index]->rect.y_size == 0)) {
                    world.create_laser(GameObject::LASER, Vector2i(position[index]->pos.x + (drawable[index]->rect.x_size * drawable[index]->scale.x) + 1,
                        position[index]->pos.y + ((drawable[index]->rect.y_size * drawable[index]->scale.y) / 2)), Vector2i(15, 0),
                        0.04, world.getClock().getElapsedTime().asSeconds());
                } else {
                    world.create_laser(GameObject::LASER, Vector2i(position[index]->pos.x
                            + (world.getResourcesManager().get_texture(drawable[index]->path).getSize().x * drawable[index]->scale.x) + 1,
                        position[index]->pos.y + ((drawable[index]->rect.y_size * drawable[index]->scale.y) / 2)), Vector2i(15, 0),
                        0.04, world.getClock().getElapsedTime().asSeconds());
                }
            }
        }
        index++;
    }
    return (0);
}
