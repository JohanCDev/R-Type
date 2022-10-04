#pragma once

#include "sparse_array.h"
#include "Entity.h"
#include "RessourcesManager.hpp"
#include <unordered_map>
#include <typeindex>
#include <any>
#include <functional>
#include "Components/ShapeComponent.hpp"
#include "Components/PositionComponent.h"
#include "Components/VelocityComponent.h"
#include "Components/CollideComponent.h"

class registry {
public:

	void register_systems(std::function<int(registry&, RessourcesManager, sf::Clock)> func) {
		this->_system_array.push_back(func);
	}

	std::vector<std::function<int(registry&, RessourcesManager, sf::Clock)>> get_systems() {
		return (this->_system_array);
	}

	template <class Component>
	sparse_array<Component>& register_components() {
		if (_components_arrays.contains(std::type_index(typeid(Component))) == false) {
			_components_arrays[std::type_index(typeid(Component))] = sparse_array<Component>();

			std::function<void(registry&, Entity const&)> erase = [](registry& r, Entity const& e) {
				sparse_array<Component>& arr = r.get_components<Component>();
				arr.erase(e);
			};
			_erase_functions_array.push_back(erase);
		}

		return std::any_cast<sparse_array<Component>&>(_components_arrays[std::type_index(typeid(Component))]);
	}
	template <class Component>
	sparse_array<Component >& get_components() {
		/*if (_components_arrays.contains(std::type_index(typeid(Component))) == false) {
			// TODO: throw
			return sparse_array<Component>();
		}*/
		return std::any_cast<sparse_array<Component>&>(_components_arrays[std::type_index(typeid(Component))]);
	}
	template <class Component>
	sparse_array<Component> const& get_components() const {
		/*if (_components_arrays.contains(std::type_index(typeid(Component))) == false) {
			// TODO: throw
			return sparse_array<Component>();
		}*/
		return std::any_cast<sparse_array<Component>&>(_components_arrays.at(std::type_index(typeid(Component))));
	}

	// Part 2.3
	Entity spawn_entity() {
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
	Entity entity_from_index(std::size_t idx) {
		return Entity(idx);
	}
	void kill_entity(Entity const& e) {
		for (auto fct : _erase_functions_array) {
			fct(*this, e);
		}
		_dead_entities_array.push_back(e);
	}
	template <typename Component >
	typename sparse_array <Component>::reference_type add_component(Entity const& to, Component&& c) {
		auto& arr = this->get_components<Component>();

		arr.insert_at(to, c);
		return arr[to];
	}
	template <typename Component, typename ... Params>
	typename sparse_array <Component>::reference_type emplace_component(Entity const& to, Params &&... p) {
		Component c(p...);

		return this->add_component(to, c);
	}
	template <typename Component >
	void remove_component(Entity const& from) {
		auto& arr = this->get_components<Component>();

		arr.erase(from);
	}

	void create_square(int length, int width, int x, int y, int x_velo, int y_velo, float refresh_time, bool collide) {
		Entity ent = this->spawn_entity();

		this->add_component<ShapeComponent>(ent, ShapeComponent(shape_type::RECTANGLE, length, width));
		this->add_component<VelocityComponent>(ent, VelocityComponent(x_velo, y_velo, refresh_time));
		this->add_component<PositionComponent>(ent, PositionComponent(x, y));
		if (collide == true) {
			this->add_component<CollideComponent>(ent, CollideComponent());
		}

	}

	void create_circle(int radius, int x, int y, int x_velo, int y_velo, float refresh_time, bool collide) {
		Entity ent = this->spawn_entity();

		this->add_component<ShapeComponent>(ent, ShapeComponent(shape_type::CIRCLE, radius));
		this->add_component<VelocityComponent>(ent, VelocityComponent(x_velo, y_velo, refresh_time));
		this->add_component<PositionComponent>(ent, PositionComponent(x, y));
		if (collide == true) {
			this->add_component<CollideComponent>(ent, CollideComponent());
		}

	}

	void create_text(std::string text, std::string font_path, int char_size, int x, int y, int x_velo, int y_velo, float refresh_time, bool collide) {
		Entity ent = this->spawn_entity();

		this->add_component<ShapeComponent>(ent, ShapeComponent(shape_type::TEXT, text, font_path, char_size));
		this->add_component<VelocityComponent>(ent, VelocityComponent(x_velo, y_velo, refresh_time));
		this->add_component<PositionComponent>(ent, PositionComponent(x, y));
		if (collide == true) {
			this->add_component<CollideComponent>(ent, CollideComponent());
		}

	}

private:
	std::unordered_map<std::type_index, std::any> _components_arrays;
	std::vector<std::function<void(registry&, Entity const&)>> _erase_functions_array;

	std::vector<std::function<int(registry&, RessourcesManager, sf::Clock)>> _system_array;

	sparse_array<Entity> _entity_array;
	std::vector<Entity> _dead_entities_array;
};
