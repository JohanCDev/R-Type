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

int bonus_system(World &world, NetworkServer &server, bonus_t &bonus_stat)
{
    auto &weapons = world.getRegistry().get_components<WeaponComponent>();
    auto &heal = world.getRegistry().get_components<HealthComponent>();
    auto &bonus = world.getRegistry().get_components<BonusComponent>();
    auto &drawables = world.getRegistry().get_components<DrawableComponent>();
    auto &positions = world.getRegistry().get_components<PositionComponent>();
    auto &speed = world.getRegistry().get_components<SpeedComponent>();
    auto &destroyables = world.getRegistry().get_components<DestroyableComponent>();
    // auto &health = world.getRegistry().get_components<HealthComponent>();
    auto &entityId = world.getRegistry().get_components<EntityIDComponent>();
    auto &teams = world.getRegistry().get_components<GameTeamComponent>();
    Message<GameMessage> sending_msg;
    std::chrono::time_point<std::chrono::steady_clock> timer;
    // int tmp = 0;
    int r = 0;
    bool bonus_bool = false;

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
                        auto &weapon = weapons[j];

                        if (check_collision(world.getResourcesManager(), sprite, otherPosition, otherDrawable) == 1 && teams[j]->team == GameTeam::PLAYER) {
                            std::cout << "hit bonus entity" << entityId[j]->id << "]."
                                      << std::endl;
                            if (bonus[i]->bonus_name == Bonus::ATTACK) {
                                weapons[j]->stat.x += 20;
                                std::pair<std::chrono::time_point<std::chrono::steady_clock>, stat_bonus_t> time;
                                time.first = std::chrono::steady_clock::now();
                                time.second.nbr = j;
                                time.second.speed = 0;
                                time.second.strengh = 1;
                                time.second.attack_speed = 0;
                                bonus_stat.timer.push_back(time);
                            } else if (bonus[i]->bonus_name == Bonus::HEAL) {
                                if (heal[j]->hp + 20 >= heal[j]->max_hp) {
                                    heal[j]->hp = heal[j]->max_hp;
                                } else {
                                    heal[j]->hp += 20;
                                }
                            } else if (bonus[i]->bonus_name == Bonus::SPEED) {
                                speed[j]->speed += 1;
                                std::pair<std::chrono::time_point<std::chrono::steady_clock>, stat_bonus_t> time;
                                time.first = std::chrono::steady_clock::now();
                                time.second.nbr = j;
                                time.second.speed = 1;
                                time.second.strengh = 0;
                                time.second.attack_speed = 0;
                                bonus_stat.timer.push_back(time);
                                r = j;
                            } else if (bonus[i]->bonus_name == Bonus::ATTACK_SPEED) {
                                weapons[j]->stat.y += 20;
                                std::pair<std::chrono::time_point<std::chrono::steady_clock>, stat_bonus_t> time;
                                time.first = std::chrono::steady_clock::now();
                                time.second.nbr = j;
                                time.second.speed = 0;
                                time.second.strengh = 0;
                                time.second.attack_speed = 1;
                                bonus_stat.timer.push_back(time);
                            }
                            sending_msg.header.id = GameMessage::S2C_ENTITY_DEAD;
                            sending_msg << entityId[i]->id;
                            world.getRegistry().kill_entity(world.getRegistry().entity_from_index(i));
                            server.SendToAll(sending_msg);
                            break;
                        }
                    }
                }
            }
        }
    }
    for(int i = 0; i < bonus_stat.timer.size(); i++) {
         std::chrono::time_point<std::chrono::steady_clock> end = std::chrono::steady_clock::now();
        double elapsed_time_ns = double(std::chrono::duration_cast<std::chrono::seconds>(end - bonus_stat.timer[i].first).count());
        if (elapsed_time_ns >= 6.0) {
            if (bonus_stat.timer[i].second.speed > 0) {
                std::cout << "je suis moins rapide" << std::endl;
                speed[bonus_stat.timer[i].second.nbr]->speed -= 1;
            } else if (bonus_stat.timer[i].second.strengh > 0) {
                std::cout << "je suis moins fort" << std::endl;
                weapons[bonus_stat.timer[i].second.nbr]->stat.x -= 20;
            } else if (bonus_stat.timer[i].second.strengh) {
                std::cout << "je suis moins attack rapide" << std::endl;
                weapons[bonus_stat.timer[i].second.nbr]->stat.y -= 20;
            }
            bonus_stat.timer.erase(bonus_stat.timer.cbegin() + i);
        }
    }
    return (0);
}
