#include "../registry.h"
#include "../Components/PositionComponent.h"
#include "../Components/VelocityComponent.h"

void velocity_system(registry &r)
{
    sparse_array<VelocityComponent> &velocity = r.get_components<VelocityComponent>();
    sparse_array<PositionComponent> &position = r.get_components<PositionComponent>();
    std::size_t index = 0;

	for (auto &i : velocity) {
        if (i && i.has_value()) {
            sf::Time elapsedTime = i->clock.getElapsedTime();
            if (elapsedTime.asSeconds() > i->seconds) {
                position[index]->x += i->x;
                position[index]->y += i->y;
                i->clock.restart();
            }
		}
        index++;
	}
}