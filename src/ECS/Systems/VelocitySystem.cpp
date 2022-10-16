#include "../Components/CollideComponent.h"
#include "../Components/ImmobileComponent.h"
#include "../Components/PositionComponent.h"
#include "../Components/VelocityComponent.h"
#include "../RessourcesManager.hpp"
#include "../registry.h"

int velocity_system(registry &r, RessourcesManager manager, sf::Clock clock)
{
    sparse_array<VelocityComponent> &velocity = r.get_components<VelocityComponent>();
    sparse_array<PositionComponent> &position = r.get_components<PositionComponent>();
    sparse_array<ImmobileComponent> &immobile = r.get_components<ImmobileComponent>();
    // sparse_array<CollideComponent> &collide = r.get_components<CollideComponent>();
    std::size_t index = 0;
    (void)manager;

    for (auto &i : velocity) {
        if (i && i.has_value()) {
            sf::Time elapsedTime = clock.getElapsedTime();
            if (elapsedTime.asSeconds() > i->seconds) {
                if (index < immobile.size() && immobile[index].has_value()) {
                    if (immobile[index]->x == false)
                        position[index]->x += i->x;
                    if (immobile[index]->y == false)
                        position[index]->y += i->y;
                } else {
                    position[index]->x += i->x;
                    position[index]->y += i->y;
                }
                i->seconds += i->coeff;
            }
        }
        index++;
    }
    return (0);
}
