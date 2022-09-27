#include "../registry.h"
#include "../Components/DrawableComponent.h"
#include "../Components/PositionComponent.h"

int drawable_system(registry &r, sf::RenderWindow &window)
{
    sparse_array<DrawableComponent> &drawable = r.get_components<DrawableComponent>();
    sparse_array<PositionComponent> &position = r.get_components<PositionComponent>();
    std::size_t index = 0;

	for (auto &i : drawable) {
        if (i && i.has_value()) {
            sf::Vector2f vec(position[index]->x, position[index]->y);
            i->sprite.setTexture(i->texture);
            i->sprite.setPosition(vec);
            window.draw(i->sprite);
		}
        index++;
	}
    return (0);
}