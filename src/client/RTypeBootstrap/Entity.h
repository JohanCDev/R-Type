#pragma once
class Entity {
public:
	// Constructor should be private
	explicit Entity(size_t id)
		: id(id) {};

	friend class registry;
	size_t id;

	operator size_t() const { return id; };
};