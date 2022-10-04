/**
 * @file CollideSystem.cpp
 * @author Cédric CORGE (cedric.corge@epitech.eu)
 * @brief 
 * @version 0.1
 * @date 2022-09-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../registry.h"

#include "../Components/PositionComponent.h"
#include "../Components/DrawableComponent.h"
#include "../Components/CollideComponent.h"
#include "../Components/VelocityComponent.h"
#include "../RessourcesManager.hpp"

int collide_system(registry &r, RessourcesManager manager, sf::Clock clock)
{
    auto &positions = r.get_components<PositionComponent>();
    auto &drawables = r.get_components<DrawableComponent>();
    auto &collides = r.get_components<CollideComponent>();
    auto &velocities = r.get_components<VelocityComponent>();
    (void)clock;

    for (size_t i = 0; i < collides.size(); ++i) {
        auto &collide = collides[i];

        if (collide) {
            auto &drawable = drawables[i];
            auto &position = positions[i];

            sf::Sprite sprite;

            sprite.setPosition(position->x, position->y);
            sprite.setTexture(manager.get_texture(drawable->path));
            sprite.setScale(drawable->x_scale, drawable->y_scale);

            for (size_t j = 0; j < collides.size(); ++j) {
                if (j != i) {
                    sf::Sprite otherSprite;
                    auto &otherCollide = collides[j];
                    auto &otherDrawable = drawables[j];
                    auto &otherPosition = positions[j];
                    auto &otherVelocity = velocities[j];

                    if (otherDrawable.has_value()) {
                        otherSprite.setPosition(otherPosition->x, otherPosition->y);
                        otherSprite.setTexture(manager.get_texture(otherDrawable->path));
                        otherSprite.setScale(otherDrawable->x_scale, otherDrawable->y_scale);
                    }

                    if (sprite.getGlobalBounds().intersects(otherSprite.getGlobalBounds())) {
                        //collide->collide = true;
                        otherPosition->x -= otherVelocity->x;
                        otherPosition->y -= otherVelocity->y;
                    }
                }
            }
        }
   }
   return (0);
}