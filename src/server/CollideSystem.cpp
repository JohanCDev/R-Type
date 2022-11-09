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

#include "../Common/Message/Message.hpp"
#include "../ECS/Components/AllComponents.hpp"
#include "../ECS/World.hpp"

/**
 * @brief Check if there is a collision on a Sprite
 *
 * @param manager Resources Manager object
 * @param sprite Sprite to check
 * @param position Optional PositionComponent
 * @param drawable Optional DrawableComponent
 * @return 1 if there is a collision
 */
int check_collision(ResourcesManager &manager, sf::Sprite sprite, std::optional<PositionComponent> &position,
    std::optional<DrawableComponent> &drawable)
{
    sf::Sprite otherSprite;
    if (drawable.has_value()) {
        otherSprite.setPosition(position->pos.x, position->pos.y);
        otherSprite.setTexture(manager.get_texture(drawable->path));
        otherSprite.setScale(drawable->scale.x, drawable->scale.y);
        if (!(drawable->rect.x == 0 && drawable->rect.y == 0 && drawable->rect.x_size == 0
                && drawable->rect.y_size == 0))
            otherSprite.setTextureRect(
                sf::IntRect(drawable->rect.x, drawable->rect.y, drawable->rect.x_size, drawable->rect.y_size));
    }
    if (sprite.getGlobalBounds().intersects(otherSprite.getGlobalBounds())) {
        return (1);
    }
    return (0);
}

int collide_system(World &world, NetworkServer &server)
{
    auto &weapons = world.getRegistry().get_components<WeaponComponent>();
    auto &drawables = world.getRegistry().get_components<DrawableComponent>();
    auto &positions = world.getRegistry().get_components<PositionComponent>();
    auto &destroyables = world.getRegistry().get_components<DestroyableComponent>();
    auto &health = world.getRegistry().get_components<HealthComponent>();
    auto &entityId = world.getRegistry().get_components<EntityIDComponent>();
    auto &teams = world.getRegistry().get_components<GameTeamComponent>();
    Message<GameMessage> sending_msg;

    for (size_t i = 0; i < weapons.size(); ++i) {
        auto &weapon = weapons[i];
        auto &position = positions[i];
        auto &drawable = drawables[i];

        if (position && drawable && weapon) {
            sf::Sprite sprite;

            sprite.setPosition(position->pos.x, position->pos.y);
            sprite.setTexture(world.getResourcesManager().get_texture(drawable->path));
            sprite.setScale(drawable->scale.x, drawable->scale.y);
            if (!(drawable->rect.x == 0 && drawable->rect.y == 0 && drawable->rect.x_size == 0
                    && drawable->rect.y_size == 0))
                sprite.setTextureRect(
                    sf::IntRect(drawable->rect.x, drawable->rect.y, drawable->rect.x_size, drawable->rect.y_size));

            for (size_t j = 0; j < destroyables.size(); ++j) {
                if (j != i && teams[i]->team != teams[j]->team) {
                    if (destroyables[j] && destroyables[j]->destroyable == true) {
                        auto &otherDrawable = drawables[j];
                        auto &otherPosition = positions[j];

                        if (check_collision(world.getResourcesManager(), sprite, otherPosition, otherDrawable) == 1) {
                            std::cout << "Entity[" << entityId[i]->id << "] hit entity[" << entityId[j]->id << "]."
                                      << std::endl;
                            health[j]->hp -= weapons[i]->stat.x;
                            health[i]->hp -= weapons[j]->stat.x;
                            if (health[j]->hp > 0) {
                                sending_msg.header.id = GameMessage::S2C_ENTITY_HIT;
                                sending_msg << entityId[j]->id;
                                sending_msg << weapons[i]->stat.x;
                                sending_msg << health[j]->max_hp;
                            } else {
                                sending_msg.header.id = GameMessage::S2C_ENTITY_DEAD;
                                sending_msg << entityId[j]->id;
                                world.getRegistry().kill_entity(world.getRegistry().entity_from_index(j));
                            }
                            server.SendToAll(sending_msg);
                            if (health[i]->hp > 0) {
                                sending_msg.header.id = GameMessage::S2C_ENTITY_HIT;
                                sending_msg << entityId[i]->id;
                                sending_msg << weapons[j]->stat.x;
                                sending_msg << health[i]->max_hp;
                            } else {
                                sending_msg.header.id = GameMessage::S2C_ENTITY_DEAD;
                                sending_msg << entityId[i]->id;
                                world.getRegistry().kill_entity(world.getRegistry().entity_from_index(i));
                            }
                            server.SendToAll(sending_msg);
                            break;
                        }
                    }
                }
            }
        }
    }
    return (0);
}
