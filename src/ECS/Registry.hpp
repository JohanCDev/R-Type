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
#include "SparseArray.hpp"
#include <unordered_map>
#include "../Common/Message/MessageType.hpp"

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
     * @param system_func 
     */
    void register_systems(std::function<int(World &)> system_func)
    {
        this->_system_array.push_back(system_func);
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

  private:
    std::unordered_map<std::type_index, std::any> _components_arrays;
    std::vector<std::function<void(registry &, Entity const &)>> _erase_functions_array;

    std::vector<std::function<int(World &)>> _system_array;

    sparse_array<Entity> _entity_array;
    std::vector<Entity> _dead_entities_array;
};
