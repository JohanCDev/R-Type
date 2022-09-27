// RTypeBootstrap.cpp : définit le point d'entrée de l'application.
//

#include "RTypeBootstrap.h"

// Part 0
#include "Entity.h"

// Part 1
#include "sparse_array.h"

// Part 2
#include "registry.h"

#include "Components/DrawableComponent.h"
#include "Components/PositionComponent.h"
#include "Components/VelocityComponent.h"
#include "Components/ControllableComponent.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

void drawable_system(registry &r, sf::RenderWindow &window);
void velocity_system(registry &r);
int controllable_system(registry& r, sf::Event event);

int main()
{
	// Part 0
	Entity e(4);

	size_t s = e;

	std::cout << "Part 0:" << std::endl << "Size = " << s << std::endl << std::endl;

	// Part 1
	sparse_array<int> vec;

	std::cout << "Part 1:" << std::endl << "Size = " << vec.size() << std::endl;

	vec.insert_at(3, 12);

	std::cout << "Size after addition = " << vec.size() << std::endl;

	if (vec[3]) {
		std::cout << "Content at spot 3 = " << *(vec[3]) << std::endl;
	}

	std::cout << "Where is 12 ? = " << vec.get_index(vec[3]) << std::endl;

	vec.emplace_at(2, 11);

	if (vec[2]) {
		std::cout << "Content at spot 2 = " << *(vec[2]) << std::endl;
	}

	std::cout << "Where is 11 ? = " << vec.get_index(vec[2]) << std::endl;

	vec.erase(2);

	if (!vec[2]) {
		std::cout << "There is no more content at spot 2" << std::endl << std::endl;
	}

	// Part 2.2
	std::cout << "Part 2:" << std::endl;

	registry r;

	r.register_components<int>();
	r.register_components<bool>();
	r.register_components<std::size_t>();

	// Part 2.3
	std::cout << "Size before first addition = " << r.get_components<int>().size() << std::endl;
	Entity newEntity = r.spawn_entity();
	std::cout << "Value of first entity = " << newEntity << std::endl;

	r.get_components<int>().insert_at(newEntity, 100);
	r.get_components<bool>().insert_at(newEntity, true);
	r.get_components<std::size_t>().insert_at(newEntity, 101);
	std::cout << "Size after first addition = " << r.get_components<int>().size() << std::endl;

	newEntity = r.spawn_entity();
	std::cout << "Value of second entity = " << newEntity << std::endl;

	r.get_components<int>().insert_at(newEntity, 100);
	r.get_components<bool>().insert_at(newEntity, true);
	r.get_components<std::size_t>().insert_at(newEntity, 101);
	std::cout << "Size after second addition = " << r.get_components<int>().size() << std::endl;

	std::cout << "[0][Int] Before killing entity [0] = " << (r.get_components<int>()[0] ? *(r.get_components<int>()[0]) : 84) << std::endl;
	std::cout << "[1][Int] Before killing entity [0] = " << (r.get_components<int>()[1] ? *(r.get_components<int>()[1]) : 84) << std::endl;
	std::cout << "[0][Size_t] Before killing entity [0] = " << (r.get_components<std::size_t>()[0] ? *(r.get_components<std::size_t>()[0]) : 84) << std::endl;
	std::cout << "[1][Size_t] Before killing entity [0] = " << (r.get_components<std::size_t>()[1] ? *(r.get_components<std::size_t>()[1]) : 84) << std::endl;
	r.kill_entity(Entity(0));
	std::cout << "Murder of entity 0" << std::endl;
	std::cout << "[0][Int] After killing entity [0] = " << (r.get_components<int>()[0] ? *(r.get_components<int>()[0]) : 84) << std::endl;
	std::cout << "[1][Int] After killing entity [0] = " << (r.get_components<int>()[1] ? *(r.get_components<int>()[1]) : 84) << std::endl;
	std::cout << "[0][Size_t] After killing entity [0] = " << (r.get_components<std::size_t>()[0] ? *(r.get_components<std::size_t>()[0]) : 84) << std::endl;
	std::cout << "[1][Size_t] After killing entity [0] = " << (r.get_components<std::size_t>()[1] ? *(r.get_components<std::size_t>()[1]) : 84) << std::endl;

	newEntity = r.spawn_entity();
	std::cout << "Value of third entity = " << newEntity << std::endl;

	r.get_components<int>().insert_at(newEntity, 100);
	r.get_components<bool>().insert_at(newEntity, true);
	r.get_components<std::size_t>().insert_at(newEntity, 101);
	std::cout << "Size after third addition = " << r.get_components<int>().size() << std::endl;

	std::cout << "[0][Int] Before removing component [Int] from [0] = " << (r.get_components<int>()[0] ? *(r.get_components<int>()[0]) : 84) << std::endl;
	std::cout << "[1][Int] Before removing component [Int] from [0] = " << (r.get_components<int>()[1] ? *(r.get_components<int>()[1]) : 84) << std::endl;
	std::cout << "[0][Size_t] Before removing component [Int] from [0] = " << (r.get_components<std::size_t>()[0] ? *(r.get_components<std::size_t>()[0]) : 84) << std::endl;
	std::cout << "[1][Size_t] Before removing component [Int] from [0] = " << (r.get_components<std::size_t>()[1] ? *(r.get_components<std::size_t>()[1]) : 84) << std::endl;
	r.remove_component<int>(Entity(0));
	std::cout << "[0][Int] After removing component [Int] from [0] = " << (r.get_components<int>()[0] ? *(r.get_components<int>()[0]) : 84) << std::endl;
	std::cout << "[1][Int] After removing component [Int] from [0] = " << (r.get_components<int>()[1] ? *(r.get_components<int>()[1]) : 84) << std::endl;
	std::cout << "[0][Size_t] After removing component [Int] from [0] = " << (r.get_components<std::size_t>()[0] ? *(r.get_components<std::size_t>()[0]) : 84) << std::endl;
	std::cout << "[1][Size_t] After removing component [Int] from [0] = " << (r.get_components<std::size_t>()[1] ? *(r.get_components<std::size_t>()[1]) : 84) << std::endl;

	newEntity = r.spawn_entity();
	r.add_component<int>(newEntity, 12);

	std::cout << "Int in newEntity = " << (r.get_components<int>()[2] ? *(r.get_components<int>()[2]) : 84) << std::endl;

	sf::RenderWindow window(sf::VideoMode(800, 600), "Hello From SFML");

	r.register_components<DrawableComponent>();
	r.register_components<PositionComponent>();
	r.register_components<VelocityComponent>();
	r.register_components<ControllableComponent>();

	Entity sprited = r.spawn_entity();
	r.add_component<DrawableComponent>(sprited, DrawableComponent("test2.png"));
	r.add_component<PositionComponent>(sprited, PositionComponent(0, 0));
	//r.add_component<VelocityComponent>(sprited, VelocityComponent(5, 5, 0.2));
	r.add_component<ControllableComponent>(sprited, ControllableComponent(sf::Keyboard::Z, sf::Keyboard::S, sf::Keyboard::D, sf::Keyboard::Q));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
			controllable_system(r, event);
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear(sf::Color::Black);
		velocity_system(r);
		drawable_system(r, window);
		window.display();
    }

	return 0;
}
