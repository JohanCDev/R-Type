/**
 * @file Registry.hpp
 * @author Cédric Corge (cedric.corge@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-10-16
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <any>
#include <functional>
#include <iostream>
#include <typeindex>
#include "Components/AllComponents.hpp"
#include "Entity.hpp"
#include "ResourcesManager.hpp"
#include "SparseArray.hpp"
#include <unordered_map>

class registry {
  public:
    void register_systems(std::function<int(registry &, ResourcesManager, sf::Clock)> func)
    {
        this->_system_array.push_back(func);
    }

    std::vector<std::function<int(registry &, ResourcesManager, sf::Clock)>> get_systems()
    {
        return (this->_system_array);
    }

    template <class Component> sparse_array<Component> &register_components()
    {
        if (_components_arrays.contains(std::type_index(typeid(Component))) == false) {
            _components_arrays[std::type_index(typeid(Component))] = sparse_array<Component>();

            std::function<void(registry &, Entity const &)> erase = [](registry &r, Entity const &e) {
                sparse_array<Component> &arr = r.get_components<Component>();
                arr.erase(e);
            };
            _erase_functions_array.push_back(erase);
        }

        return std::any_cast<sparse_array<Component> &>(_components_arrays[std::type_index(typeid(Component))]);
    }
    template <class Component> sparse_array<Component> &get_components()
    {
        /*if (_components_arrays.contains(std::type_index(typeid(Component))) == false) {
            // TODO: throw
            return sparse_array<Component>();
        }*/
        return std::any_cast<sparse_array<Component> &>(_components_arrays[std::type_index(typeid(Component))]);
    }
    template <class Component> sparse_array<Component> const &get_components() const
    {
        /*if (_components_arrays.contains(std::type_index(typeid(Component))) == false) {
            // TODO: throw
            return sparse_array<Component>();
        }*/
        return std::any_cast<sparse_array<Component> &>(_components_arrays.at(std::type_index(typeid(Component))));
    }

    // Part 2.3
    Entity spawn_entity()
    {
        std::size_t idx;

        if (_dead_entities_array.empty()) {
            auto max_id = _entity_array.size();
            _entity_array.insert_at(max_id, Entity(max_id));
            return Entity(max_id);
        }
        idx = _dead_entities_array.back();
        _dead_entities_array.pop_back();
        return this->entity_from_index(idx);
    }
    Entity entity_from_index(std::size_t idx)
    {
        return Entity(idx);
    }
    void kill_entity(Entity const &e)
    {
        for (auto fct : _erase_functions_array) {
            fct(*this, e);
        }
        _dead_entities_array.push_back(e);
    }
    template <typename Component>
    typename sparse_array<Component>::reference_type add_component(Entity const &to, Component &&c)
    {
        auto &arr = this->get_components<Component>();

        arr.insert_at(to, c);
        return arr[to];
    }
    template <typename Component, typename... Params>
    typename sparse_array<Component>::reference_type emplace_component(Entity const &to, Params &&...p)
    {
        Component c(p...);

        return this->add_component(to, c);
    }
    template <typename Component> void remove_component(Entity const &from)
    {
        auto &arr = this->get_components<Component>();

        arr.erase(from);
    }

    void create_laser(int x, int y, int x_velo, int y_velo, float refresh_time, float elapsed_time)
    {
        Entity ent = this->spawn_entity();

        this->add_component<DrawableComponent>(ent, DrawableComponent("r-typesheet1.gif", Vector4(104, 171, 80, 14)));
        this->add_component<WeaponComponent>(ent, WeaponComponent("laser", 5, 15, 0.2));
        this->add_component<VelocityComponent>(ent, VelocityComponent(x_velo, y_velo, refresh_time, elapsed_time));
        this->add_component<PositionComponent>(ent, PositionComponent(x, y));
    }

    void create_player(std::string texture_path, Vector4 texture_rec, float x_scale, float y_scale, int pos_x,
        int pos_y, int hp, int speed_x, int speed_y, float refresh_time, KeyboardInput up, KeyboardInput down,
        KeyboardInput right, KeyboardInput left, MouseInput shoot)
    {
        Entity ent = this->spawn_entity();

        this->add_component<DrawableComponent>(ent, DrawableComponent(texture_path, texture_rec, x_scale, y_scale));
        this->add_component<PositionComponent>(ent, PositionComponent(pos_x, pos_y));
        this->add_component<ImmobileComponent>(ent, ImmobileComponent(true, true));
        this->add_component<CollideComponent>(ent, CollideComponent());
        this->add_component<HealthComponent>(ent, (HealthComponent(hp)));
        this->add_component<VelocityComponent>(ent, VelocityComponent(speed_x, speed_y, refresh_time));
        this->add_component<ControllableComponent>(ent, ControllableComponent(up, down, right, left, shoot));
    }

    void create_enemy(std::string texture_path, Vector4 texture_rec, float x_scale, float y_scale, int pos_x, int pos_y,
        int speed_x, int speed_y, float refresh_time)
    {
        Entity ent = this->spawn_entity();

        this->add_component<DrawableComponent>(ent, DrawableComponent(texture_path, texture_rec, x_scale, y_scale));
        this->add_component<PositionComponent>(ent, PositionComponent(pos_x, pos_y));
        this->add_component<ImmobileComponent>(ent, ImmobileComponent(false, false));
        this->add_component<CollideComponent>(ent, CollideComponent());
        this->add_component<WeaponComponent>(ent, WeaponComponent("meteor", 1, 1, 0));
        this->add_component<DestroyableComponent>(ent, DestroyableComponent(true));
        this->add_component<VelocityComponent>(ent, VelocityComponent(speed_x, speed_y, refresh_time));
    }

  private:
    std::unordered_map<std::type_index, std::any> _components_arrays;
    std::vector<std::function<void(registry &, Entity const &)>> _erase_functions_array;

    std::vector<std::function<int(registry &, ResourcesManager, sf::Clock)>> _system_array;

    sparse_array<Entity> _entity_array;
    std::vector<Entity> _dead_entities_array;
};
