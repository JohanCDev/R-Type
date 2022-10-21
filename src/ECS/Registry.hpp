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

class World;

/**
 * @brief Storage of all sparse_array
 * 
 */
class registry {
  public:

    /**
     * @brief Register a new system into the system sparse array
     * 
     * @param func 
     */
    void register_systems(std::function<int(World &)> func)
    {
        this->_system_array.push_back(func);
    }

    /**
     * @brief Get the systems array
     * 
     * @return std::vector<std::function<int(World &)>> 
     */
    std::vector<std::function<int(World &)>> get_systems()
    {
        return (this->_system_array);
    }

    /**
     * @brief Register a new component by creating his own sparse array
     * 
     * @tparam Component 
     * @return sparse_array<Component>& 
     */
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

    /**
     * @brief Get the sparse array of the specified component
     * 
     * @tparam Component 
     * @return sparse_array<Component>& 
     */
    template <class Component> sparse_array<Component> &get_components()
    {
        /*if (_components_arrays.contains(std::type_index(typeid(Component))) == false) {
            // TODO: throw
            return sparse_array<Component>();
        }*/
        return std::any_cast<sparse_array<Component> &>(_components_arrays[std::type_index(typeid(Component))]);
    }

    /**
     * @brief Get the constant sparse array of the specified component
     * 
     * @tparam Component 
     * @return sparse_array<Component> const& 
     */
    template <class Component> sparse_array<Component> const &get_components() const
    {
        /*if (_components_arrays.contains(std::type_index(typeid(Component))) == false) {
            // TODO: throw
            return sparse_array<Component>();
        }*/
        return std::any_cast<sparse_array<Component> &>(_components_arrays.at(std::type_index(typeid(Component))));
    }

    /**
     * @brief Generate a new entity
     * 
     * @return Entity 
     */
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

    /**
     * @brief Get entity from index
     * 
     * @param idx 
     * @return Entity 
     */
    Entity entity_from_index(std::size_t idx)
    {
        return Entity(idx);
    }

    /**
     * @brief Remove the specified entity
     * 
     * @param e 
     */
    void kill_entity(Entity const &e)
    {
        for (auto fct : _erase_functions_array) {
            fct(*this, e);
        }
        _dead_entities_array.push_back(e);
    }

    /**
     * @brief Add a component to his sparse array
     * 
     * @tparam Component 
     * @param to 
     * @param c 
     * @return sparse_array<Component>::reference_type 
     */
    template <typename Component>
    typename sparse_array<Component>::reference_type add_component(Entity const &to, Component &&c)
    {
        auto &arr = this->get_components<Component>();

        arr.insert_at(to, c);
        return arr[to];
    }

    /**
     * @brief Build and add a component to his sparse array
     * 
     * @tparam Component 
     * @tparam Params 
     * @param to 
     * @param p 
     * @return sparse_array<Component>::reference_type 
     */
    template <typename Component, typename... Params>
    typename sparse_array<Component>::reference_type emplace_component(Entity const &to, Params &&...p)
    {
        Component c(p...);

        return this->add_component(to, c);
    }

    /**
     * @brief Remove a component from his sparse array
     * 
     * @tparam Component 
     * @param from 
     */
    template <typename Component> void remove_component(Entity const &from)
    {
        auto &arr = this->get_components<Component>();

        arr.erase(from);
    }

    /**
     * @brief Create a laser entity
     * 
     * @param x 
     * @param y 
     * @param x_velo 
     * @param y_velo 
     * @param refresh_time 
     * @param elapsed_time 
     */
    void create_laser(int x, int y, int x_velo, int y_velo, float refresh_time, float elapsed_time)
    {
        Entity ent = this->spawn_entity();

        this->add_component<DrawableComponent>(ent, DrawableComponent("r-typesheet1.gif", Vector4(104, 171, 80, 14)));
        this->add_component<WeaponComponent>(ent, WeaponComponent("laser", 5, 15, 0.2));
        this->add_component<VelocityComponent>(ent, VelocityComponent(x_velo, y_velo, refresh_time, elapsed_time));
        this->add_component<PositionComponent>(ent, PositionComponent(x, y));
    }

    /**
     * @brief Create a player entity
     * 
     * @param texture_path 
     * @param texture_rec 
     * @param x_scale 
     * @param y_scale 
     * @param pos_x 
     * @param pos_y 
     * @param hp 
     * @param speed_x 
     * @param speed_y 
     * @param refresh_time 
     * @param up 
     * @param down 
     * @param right 
     * @param left 
     * @param shoot 
     */
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

    /**
     * @brief Create a enemy entity
     * 
     * @param texture_path 
     * @param texture_rec 
     * @param x_scale 
     * @param y_scale 
     * @param pos_x 
     * @param pos_y 
     * @param speed_x 
     * @param speed_y 
     * @param refresh_time 
     * @param up 
     * @param down 
     * @param right 
     * @param left 
     * @param shoot 
     */
    void create_enemy(std::string texture_path, Vector4 texture_rec, float x_scale, float y_scale, int pos_x, int pos_y,
        int speed_x, int speed_y, float refresh_time, KeyboardInput up, KeyboardInput down, KeyboardInput right,
        KeyboardInput left, MouseInput shoot)
    {
        Entity ent = this->spawn_entity();

        this->add_component<DrawableComponent>(ent, DrawableComponent(texture_path, texture_rec, x_scale, y_scale));
        this->add_component<PositionComponent>(ent, PositionComponent(pos_x, pos_y));
        this->add_component<ImmobileComponent>(ent, ImmobileComponent(false, false));
        this->add_component<CollideComponent>(ent, CollideComponent());
        this->add_component<WeaponComponent>(ent, WeaponComponent("meteor", 1, 1, 0));
        this->add_component<DestroyableComponent>(ent, DestroyableComponent(true));
        this->add_component<VelocityComponent>(ent, VelocityComponent(speed_x, speed_y, refresh_time));
        this->add_component<ControllableComponent>(ent, ControllableComponent(up, down, right, left, shoot));
    }

  private:
    std::unordered_map<std::type_index, std::any> _components_arrays;
    std::vector<std::function<void(registry &, Entity const &)>> _erase_functions_array;

    std::vector<std::function<int(World &)>> _system_array;

    sparse_array<Entity> _entity_array;
    std::vector<Entity> _dead_entities_array;
};
