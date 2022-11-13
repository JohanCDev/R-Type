/**
 * @file CollideSystem.cpp
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

int check_collision(DrawableComponent &drawable, PositionComponent &pos, DrawableComponent &otherDrawable, PositionComponent &otherPos)
{
    if (pos.pos.x + drawable.rect.x_size * drawable.scale.x < otherPos.pos.x)
        return (0);
    if (pos.pos.y + drawable.rect.y_size * drawable.rect.y < otherPos.pos.y)
        return (0);
    if (pos.pos.x + otherDrawable.rect.x_size * otherDrawable.scale.x < pos.pos.x)
        return (0);
    if (pos.pos.y + otherDrawable.rect.y_size * otherDrawable.rect.y < pos.pos.y)
        return (0);
    return (1);
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
    std::srand(std::time(nullptr));
    int random_variable = std::rand();

    for (size_t i = 0; i < weapons.size(); ++i) {
        auto &weapon = weapons[i];
        auto &position = positions[i];
        auto &drawable = drawables[i];

        if (position && drawable && weapon) {

            for (size_t j = 0; j < destroyables.size(); ++j) {
                if (j != i && teams[i]->team != teams[j]->team && teams[i]->team != GameTeam::NEUTRAL
                    && teams[j]->team != GameTeam::NEUTRAL) {
                    if (destroyables[j] && destroyables[j]->destroyable == true) {
                        auto &otherDrawable = drawables[j];
                        auto &otherPosition = positions[j];

                        /* if (!(drawable && drawable.has_value() && position && position.has_value() && otherDrawable
                                && otherDrawable.has_value() && otherPosition && otherPosition.has_value()))
                            continue;*/
                        if (check_collision(drawable.value(), position.value(), otherDrawable.value(), otherPosition.value())
                            == 1) {
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
                                if (teams[j]->team == GameTeam::ENEMY && random_variable % 3 == 0) {
                                    bonus_creation(world, server, positions[j]->pos);
                                }
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
