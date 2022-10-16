/**
 * @file ShootingSystem.cpp
 * @author Cédric Corge (cedric.corge@epitech.eu)
 * @brief 
 * @version 0.1
 * @date 2022-10-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../registry.h"
#include "../RessourcesManager.hpp"
#include "../Components/WeaponComponent.h"
#include "../Components/PositionComponent.h"
#include "../Components/HealthComponent.h"
#include "../Components/DestroyableComponent.hpp"

int check_collision(RessourcesManager &manager, sf::Sprite sprite, std::optional<PositionComponent> &position, std::optional<DrawableComponent> &drawable)
{
    sf::Sprite otherSprite;
    if (drawable.has_value()) {
        otherSprite.setPosition(position->x, position->y);
        otherSprite.setTexture(manager.get_texture(drawable->path));
        otherSprite.setScale(drawable->x_scale, drawable->y_scale);
        if (!(drawable->rect.x == 0 && drawable->rect.y == 0 && drawable->rect.x_size == 0 && drawable->rect.y_size == 0))
            otherSprite.setTextureRect(sf::IntRect(drawable->rect.x, drawable->rect.y, drawable->rect.x_size, drawable->rect.y_size));
    }
    if (sprite.getGlobalBounds().intersects(otherSprite.getGlobalBounds())) {
        return (1);
    }
    return (0);
}

int shooting_system(registry &r, RessourcesManager manager, sf::Clock clock)
{
    auto &weapons = r.get_components<WeaponComponent>();
    auto &drawables = r.get_components<DrawableComponent>();
    auto &positions = r.get_components<PositionComponent>();
    auto &destroyables = r.get_components<DestroyableComponent>();
    auto &healths = r.get_components<HealthComponent>();

    (void)clock;
    for (size_t i = 0; i < weapons.size(); ++i) {
        auto &weapon = weapons[i];
        auto &position = positions[i];
        auto &drawable = drawables[i];

        if (position && drawable && weapon) {

            sf::Sprite sprite;

            sprite.setPosition(position->x, position->y);
            sprite.setTexture(manager.get_texture(drawable->path));
            sprite.setScale(drawable->x_scale, drawable->y_scale);
            if (!(drawable->rect.x == 0 && drawable->rect.y == 0 && drawable->rect.x_size == 0 && drawable->rect.y_size == 0))
                sprite.setTextureRect(sf::IntRect(drawable->rect.x, drawable->rect.y, drawable->rect.x_size, drawable->rect.y_size));

            for (size_t j = 0; j < destroyables.size(); ++j) {
                if (j != i) {
                    if (destroyables[j] && destroyables[j]->destroyable == true) {
                        auto &otherDrawable = drawables[j];
                        auto &otherPosition = positions[j];

                        if (check_collision(manager, sprite, otherPosition, otherDrawable) == 1) {
                            r.kill_entity(r.entity_from_index(j));
                            r.kill_entity(r.entity_from_index(i));
                            break;
                        }
                    }
                }
            }

            for (size_t j = 0; j < healths.size(); ++j) {
                if (j != i) {
                    auto &otherDrawable = drawables[j];
                    auto &otherPosition = positions[j];

                    if (check_collision(manager, sprite, otherPosition, otherDrawable) == 1) {
                        r.kill_entity(r.entity_from_index(i));
                        healths[j]->hp -= 1;
                        if (healths[j]->hp == 0) {
                            r.kill_entity(r.entity_from_index(j));
                        }
                        break;
                    }
                }
            }
        }
    }
    return (0);
}