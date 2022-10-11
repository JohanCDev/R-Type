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
#include "Components/ImmobileComponent.h"
#include "Components/CollideComponent.h"
#include "Components/ShapeComponent.hpp"
#include "Components/WeaponComponent.h"

#include "RessourcesManager.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

int drawable_system(registry &r, sf::RenderWindow &window, RessourcesManager manager);
int velocity_system(registry &r, RessourcesManager manager, sf::Clock clock);
int shooting_system(registry &r, RessourcesManager manager, sf::Clock clock);
int collide_system(registry &r, RessourcesManager manager, sf::Clock clock);
int controllable_system(registry& r, RessourcesManager manager, sf::Event event, sf::Clock clock);
int shape_system(registry &r, sf::RenderWindow &window, RessourcesManager manager);

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
	r.register_components<ImmobileComponent>();
	r.register_components<ControllableComponent>();
	r.register_components<CollideComponent>();
	r.register_components<ShapeComponent>();
	r.register_components<WeaponComponent>();

	r.register_systems(&shooting_system);
	r.register_systems(&velocity_system);

	RessourcesManager manager;

	manager.register_texture("test2.png");
	manager.register_texture("chat.png");
	manager.register_texture("panda.png");
	manager.register_texture("r-typesheet1.gif");

	//Entity text = r.spawn_entity();

	//r.add_component<ShapeComponent>(text, ShapeComponent(shape_type::TEXT, "test", "default_font", 20));
	//r.add_component<PositionComponent>(text, PositionComponent(10, 100));

	Entity sprited = r.spawn_entity();
	r.add_component<DrawableComponent>(sprited, DrawableComponent("chat.png", Vector4(0, 0, 0, 0), 0.2, 0.2));
	r.add_component<PositionComponent>(sprited, PositionComponent(0, 0));
	r.add_component<ImmobileComponent>(sprited, ImmobileComponent(false, false));
	r.add_component<CollideComponent>(sprited, CollideComponent());
	r.add_component<VelocityComponent>(sprited, VelocityComponent(0, 0, 0.2));
	r.add_component<ControllableComponent>(sprited, ControllableComponent(KeyboardInput::Z, KeyboardInput::S, KeyboardInput::D, KeyboardInput::Q, MouseInput::Left_click));

	Entity sprite = r.spawn_entity();
	r.add_component<DrawableComponent>(sprite, DrawableComponent("panda.png", Vector4(0, 0, 0, 0), 0.2, 0.2));
	r.add_component<PositionComponent>(sprite, PositionComponent(500, 0));
	r.add_component<ImmobileComponent>(sprite, ImmobileComponent(true, true));
	r.add_component<CollideComponent>(sprite, CollideComponent());
	r.add_component<VelocityComponent>(sprite, VelocityComponent(5, 5, 0.2));
	r.add_component<ControllableComponent>(sprite, ControllableComponent(KeyboardInput::Up, KeyboardInput::Down, KeyboardInput::Right, KeyboardInput::Left, MouseInput::UNDEFINED));

	//r.create_text("test", "default_font", 20, 500, 300, -1, -1, 0.2, true);


	sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;

		
        while (window.pollEvent(event)) {
			if (controllable_system(r, manager, event, clock) == 1)
				continue;
			//
			if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
		
        window.clear(sf::Color::White);
		
		for (auto &system : r.get_systems()) {
			system(r, manager, clock);
		}
		
		//
		drawable_system(r, window, manager);
		//
		
		window.display();
    }

	return 0;
}
