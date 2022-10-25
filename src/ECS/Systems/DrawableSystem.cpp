/**
 * @file DrawableSystem.cpp
 * @author Cédric Corge (cedric.corge@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-10-16
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "../Components/AllComponents.hpp"
#include "../Registry.hpp"
#include "../ResourcesManager.hpp"
#include "../World.hpp"

int drawable_system(World &world)
{
    sparse_array<DrawableComponent> &drawable = world.getRegistry().get_components<DrawableComponent>();
    sparse_array<PositionComponent> &position = world.getRegistry().get_components<PositionComponent>();
    sparse_array<HealthComponent> &health = world.getRegistry().get_components<HealthComponent>();
    std::size_t index = 0;
    sf::Sprite sprite;
    sf::Texture texture;

    for (auto &i : drawable) {
        if (i && i.has_value()) {
            if (health[index].has_value() && health[index]->hp > 0) {
                sf::Vector2f vec{position[index]->pos.x, position[index]->pos.y};
                texture = world.getResourcesManager().get_texture(i->path);
                if (!(i->rect.x == 0 && i->rect.y == 0 && i->rect.x_size == 0 && i->rect.y_size == 0)) {
                    sprite.setTextureRect(sf::IntRect(i->rect.x, i->rect.y, i->rect.x_size, i->rect.y_size));
                }

                sprite.setTexture(texture);
                sprite.setPosition(vec);
                sprite.setScale(i->scale.x, i->scale.y);
                world.getWindow().draw(sprite);
            }
        }
        index++;
    }
    return (0);
}
