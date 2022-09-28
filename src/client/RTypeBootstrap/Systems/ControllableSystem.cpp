#include "../registry.h"
#include "../Components/ControllableComponent.h"
#include "../Components/PositionComponent.h"
#include "../Components/VelocityComponent.h"
#include "../Components/CollideComponent.h"
#include <iostream>

int controllable_system(registry &r, sf::Event event)
{
	sparse_array<ControllableComponent> &controllable = r.get_components<ControllableComponent>();
	sparse_array<VelocityComponent> &velocity = r.get_components<VelocityComponent>();
	sparse_array<PositionComponent> &position = r.get_components<PositionComponent>();
	sparse_array<CollideComponent> &collide = r.get_components<CollideComponent>();
	std::size_t index = 0;

	for (auto const& i : controllable) {
		if (i && i.has_value()) {
			if (index < collide.size()) {
				if (collide[index]->collide == true) {
					return (0);
				}
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == i->up) {
				position[index]->y -= velocity[index]->y;
				return (1);
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == i->down) {
				position[index]->y += velocity[index]->y;
				return (1);
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == i->left) {
				position[index]->x -= velocity[index]->x;
				return (1);
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == i->right) {
				position[index]->x += velocity[index]->x;
				return (1);
			}
		}
		index++;
	}
	return (0);
}