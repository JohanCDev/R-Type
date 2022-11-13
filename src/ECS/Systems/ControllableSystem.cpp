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
#include "../Common/Message/Message.hpp"
#include "../Common/Message/MessageType.hpp"
#include "../Components/AllComponents.hpp"
#include "../Registry.hpp"
#include "../ResourcesManager.hpp"
#include "../World.hpp"

/**
 * @brief Get the Shoot Position of the entity
 *
 * @param world The world
 * @param position Position of the entity
 * @param drawable Drawable of the entity
 * @return Vector2f The position of the shoot
 */
Vector2f getShootPosition(
    World &world, std::optional<PositionComponent> position, std::optional<DrawableComponent> drawable)
{
    Vector2f shoot_pos;

    sf::Texture texture = world.getResourcesManager().get_texture(drawable->path);

    shoot_pos.x = position->pos.x + (texture.getSize().x * drawable->scale.x) + 1.0f;
    shoot_pos.y = position->pos.y + ((texture.getSize().y * drawable->scale.y) / 2.0f);
    return (shoot_pos);
}

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
                Vector2f shoot_pos = getShootPosition(world, position[index], drawable[index]);
                if (!(drawable[index]->rect.x == 0 && drawable[index]->rect.y == 0 && drawable[index]->rect.x_size == 0
                        && drawable[index]->rect.y_size == 0)) {
                    world.create_laser(GameObject::LASER, GameTeam::PLAYER, shoot_pos, Vector2i{15, 0}, 0.04f);
                } else {
                    world.create_laser(
                        GameObject::LASER, GameTeam::PLAYER, shoot_pos, Vector2i{15, 0}, 0.04f);
                }
            }
        }
        index++;
    }
    return (0);
}
