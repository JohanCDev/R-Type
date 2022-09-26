#include "../registry.h"
#include "../Components/ControllableComponent.h"
#include "../Components/PositionComponent.h"

int controllable_system(registry &r, sf::Event event)
{
	sparse_array<ControllableComponent> &controllable = r.get_components<ControllableComponent>();
	sparse_array<PositionComponent> &position = r.get_components<PositionComponent>();
	std::size_t index = 0;

	for (auto const& i : controllable) {
		if (i && i.has_value()) {
			if (event.type == sf::Event::KeyPressed && event.key.code == i->up) {
				position[index]->y -= 5;
				return (1);
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == i->down) {
				position[index]->y += 5;
				return (1);
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == i->left) {
				position[index]->x -= 5;
				return (1);
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == i->right) {
				position[index]->x += 5;
				return (1);
			}
		}
		index++;
	}
	return (0);
}