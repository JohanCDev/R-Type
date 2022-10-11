#include "../registry.h"
#include "../Components/ControllableComponent.h"
#include "../Components/ShapeComponent.hpp"
#include "../Components/PositionComponent.h"
#include "../Components/VelocityComponent.h"
#include "../Components/CollideComponent.h"
#include "../Components/DrawableComponent.h"
#include "../Components/ImmobileComponent.h"
#include "../RessourcesManager.hpp"
#include <iostream>

int controllable_system(registry &r, RessourcesManager manager, sf::Event event, sf::Clock game_clock)
{
	sparse_array<ControllableComponent> &controllable = r.get_components<ControllableComponent>();
	sparse_array<VelocityComponent> &velocity = r.get_components<VelocityComponent>();
	sparse_array<PositionComponent> &position = r.get_components<PositionComponent>();
	sparse_array<DrawableComponent> &drawable = r.get_components<DrawableComponent>();
	std::size_t index = 0;
	(void)manager;

	for (auto const& i : controllable) {
		if (i && i.has_value()) {
			if (event.type == sf::Event::KeyPressed && (KeyboardInput)event.key.code == i->up) {
				position[index]->y -= velocity[index]->y;
				return (1);
			}
			if (event.type == sf::Event::KeyPressed && (KeyboardInput)event.key.code == i->down) {
				position[index]->y += velocity[index]->y;
				return (1);
			}
			if (event.type == sf::Event::KeyPressed && (KeyboardInput)event.key.code == i->left) {
				position[index]->x -= velocity[index]->x;
				return (1);
			}
			if (event.type == sf::Event::KeyPressed && (KeyboardInput)event.key.code == i->right) {
				position[index]->x += velocity[index]->x;
				return (1);
			}
			if (event.type == sf::Event::MouseButtonPressed && (MouseInput)event.mouseButton.button == i->shoot) {
				sf::Sprite sprite;
				sprite.setPosition(position[index]->x, position[index]->y);
            	sprite.setTexture(manager.get_texture(drawable[index]->path));
            	sprite.setScale(drawable[index]->x_scale, drawable[index]->y_scale);
            	//sprite.setTextureRect(sf::IntRect(drawable[index]->rect.x, drawable[index]->rect.y, drawable[index]->rect.x_size, drawable[index]->rect.y_size));
				r.create_laser(position[index]->x + (sprite.getTexture()->getSize().x * drawable[index]->x_scale) + 1, position[index]->y, 15, 0, 0.2, game_clock.getElapsedTime().asSeconds());
			}
		}
		index++;
	}
	return (0);
}