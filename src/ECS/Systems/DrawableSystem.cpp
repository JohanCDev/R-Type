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
    std::size_t index = 0;
    sf::Sprite sprite;
    sf::Texture texture;

    for (auto &i : drawable) {
        if (i && i.has_value()) {
            sf::Vector2f vec(position[index]->x, position[index]->y);
            texture = world.getRessourcesManager().get_texture(i->path);
            if (!(i->rect.x == 0 && i->rect.y == 0 && i->rect.x_size == 0 && i->rect.y_size == 0)) {
                sprite.setTextureRect(sf::IntRect(i->rect.x, i->rect.y, i->rect.x_size, i->rect.y_size));
            }

            sprite.setTexture(texture);
            sprite.setPosition(vec);
            sprite.setScale(i->x_scale, i->y_scale);
            world.getWindow().draw(sprite);
        }
        index++;
    }
    return (0);
}
