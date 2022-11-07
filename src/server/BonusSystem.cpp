/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** BoostSystem
*/

// #include "BoostSystem.hpp"
#include "../Common/Message/Message.hpp"
#include "../Common/Message/MessageType.hpp"
#include "../ECS/Components/AllComponents.hpp"
// #include "ShootingSystem.hpp"
#include "../ECS/World.hpp"
#include "game.hpp"
#include "server.hpp"

// int check_collision(ResourcesManager &manager, sf::Sprite sprite, std::optional<PositionComponent> &position,
//     std::optional<DrawableComponent> &drawable)
// {
//     sf::Sprite otherSprite;
//     if (drawable.has_value()) {
//         otherSprite.setPosition(position->pos.x, position->pos.y);
//         otherSprite.setTexture(manager.get_texture(drawable->path));
//         otherSprite.setScale(drawable->scale.x, drawable->scale.y);
//         if (!(drawable->rect.x == 0 && drawable->rect.y == 0 && drawable->rect.x_size == 0
//                 && drawable->rect.y_size == 0))
//             otherSprite.setTextureRect(
//                 sf::IntRect(drawable->rect.x, drawable->rect.y, drawable->rect.x_size, drawable->rect.y_size));
//     }
//     if (sprite.getGlobalBounds().intersects(otherSprite.getGlobalBounds())) {
//         return (1);
//     }
//     return (0);
// }

int bonus_system(World &world, NetworkServer &server)
{
    // auto &weapons = world.getRegistry().get_components<WeaponComponent>();
    auto &bonus = world.getRegistry().get_components<BonusComponent>();
    auto &drawables = world.getRegistry().get_components<DrawableComponent>();
    auto &positions = world.getRegistry().get_components<PositionComponent>();
    auto &destroyables = world.getRegistry().get_components<DestroyableComponent>();
    // auto &health = world.getRegistry().get_components<HealthComponent>();
    auto &entityId = world.getRegistry().get_components<EntityIDComponent>();
    auto &teams = world.getRegistry().get_components<GameTeamComponent>();
    Message<GameMessage> sending_msg;

    for (size_t i = 0; i < bonus.size(); ++i) {
        // std::cout << "j'ai trouvé un bonus" << std::endl;
        auto &bonus_tmp = bonus[i];
        auto &position = positions[i];
        auto &drawable = drawables[i];

        if (position && drawable && bonus_tmp) {
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
                            std::cout << "hit bonus entity" << entityId[j]->id << "]."
                                      << std::endl;
                            sending_msg.header.id = GameMessage::S2C_ENTITY_DEAD;
                            sending_msg << entityId[i]->id;
                            world.getRegistry().kill_entity(world.getRegistry().entity_from_index(i));
                            server.SendToAll(sending_msg);
                                // std::cout << "l'entité est morte" << std::endl;
                            // exit(0);
                            // health[j]->hp -= bonus[i]->stat.x;
                            // health[i]->hp -= bonus[j]->stat.x;
                            // if (health[j]->hp > 0) {
                            //     sending_msg.header.id = GameMessage::S2C_ENTITY_HIT;
                            //     sending_msg << entityId[j]->id;
                            //     // sending_msg << bonus[i]->stat.x;
                            //     sending_msg << health[j]->max_hp;
                            // } else {
                            //     sending_msg.header.id = GameMessage::S2C_ENTITY_DEAD;
                            //     sending_msg << entityId[j]->id;
                            //     bonus_creation(world, server, positions[j]->pos);
                            //     world.getRegistry().kill_entity(world.getRegistry().entity_from_index(j));
                            //     // std::cout << "l'entité est morte" << std::endl;
                            // }
                            // server.SendToAll(sending_msg);
                            // if (health[i]->hp > 0) {
                            //     sending_msg.header.id = GameMessage::S2C_ENTITY_HIT;
                            //     sending_msg << entityId[i]->id;
                            //     sending_msg << bonus[j]->stat.x;
                            //     sending_msg << health[i]->max_hp;
                            // } else {
                            //     sending_msg.header.id = GameMessage::S2C_ENTITY_DEAD;
                            //     sending_msg << entityId[i]->id;
                            //     world.getRegistry().kill_entity(world.getRegistry().entity_from_index(i));
                            // }
                            // server.SendToAll(sending_msg);
                            break;
                        }
                    }
                }
            }
        }
    }
    return (0);
}
