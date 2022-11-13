/**
 * @file World.cpp
 * @author Cédric Corge (cedric.corge@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-10-17
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "World.hpp"
#include <iostream>

World::World(bool client) : _r(), _manager(), _clock(), _player_direction({0, 0})
{
    (void)client;
    this->_r.register_components<ClientIDComponent>();
    this->_r.register_components<CollideComponent>();
    this->_r.register_components<ControllableComponent>();
    this->_r.register_components<DestroyableComponent>();
    this->_r.register_components<DrawableComponent>();
    this->_r.register_components<EntityIDComponent>();
    this->_r.register_components<GameObjectComponent>();
    this->_r.register_components<GameTeamComponent>();
    this->_r.register_components<HealthComponent>();
    this->_r.register_components<ImmobileComponent>();
    this->_r.register_components<PositionComponent>();
    this->_r.register_components<VelocityComponent>();
    this->_r.register_components<WeaponComponent>();
    this->_r.register_components<TextComponent>();
    this->_r.register_components<BonusComponent>();
    this->_r.register_components<SoundEffectComponent>();
    this->_r.register_components<SpeedComponent>();
    this->_r.register_components<ClickableComponent>();
    this->_r.register_components<DoubleLaserComponent>();
    this->_r.register_components<LevelComponent>();

    this->_manager.register_font("assets/font/EMINOR-BlackItalic.ttf");

    this->register_all_drawable_object();
}

World::World() : _r(), _clock()
{
    this->_r.register_components<ClientIDComponent>();
    this->_r.register_components<CollideComponent>();
    this->_r.register_components<ControllableComponent>();
    this->_r.register_components<DestroyableComponent>();
    this->_r.register_components<DrawableComponent>();
    this->_r.register_components<EntityIDComponent>();
    this->_r.register_components<GameObjectComponent>();
    this->_r.register_components<GameTeamComponent>();
    this->_r.register_components<HealthComponent>();
    this->_r.register_components<ImmobileComponent>();
    this->_r.register_components<PositionComponent>();
    this->_r.register_components<VelocityComponent>();
    this->_r.register_components<WeaponComponent>();
    this->_r.register_components<BonusComponent>();
    this->_r.register_components<SoundEffectComponent>();
    this->_r.register_components<SpeedComponent>();
    this->_r.register_components<TextComponent>();
    this->_r.register_components<ClickableComponent>();
    this->_r.register_components<DoubleLaserComponent>();
    this->_r.register_components<LevelComponent>();

    this->register_all_assets();
    this->register_all_drawable_object();
}

World::~World()
{
}

void World::register_all_assets()
{
    this->_manager.register_texture("assets/r-typesheet1.gif");
    this->_manager.register_texture("assets/r-typesheet5.gif");
    this->_manager.register_texture("assets/r-typesheet39.gif");
    this->_manager.register_texture("assets/background/menu.jpg");
    this->_manager.register_texture("assets/background/lobby.png");
    this->_manager.register_texture("assets/background/bg-boutton.png");
    this->_manager.register_texture("assets/SpaceShip/ship_armored_spritesheet.png");
    this->_manager.register_texture("assets/SpaceShip/ship_damage_spritesheet.png");
    this->_manager.register_texture("assets/SpaceShip/ship_engineer_spritesheet.png");
    this->_manager.register_texture("assets/SpaceShip/ship_sniper_spritesheet.png");
    this->_manager.register_texture("assets/SpaceShip/enemy_focus.png");
    this->_manager.register_texture("assets/SpaceShip/enemy_kamikaze.png");
    this->_manager.register_texture("assets/SpaceShip/enemy_sniper.png");
    this->_manager.register_texture("assets/Stats/attack_speed.png");
    this->_manager.register_texture("assets/Stats/boost_attack.png");
    this->_manager.register_texture("assets/Stats/boost_hp.png");
    this->_manager.register_texture("assets/Stats/speed.png");
    this->_manager.register_texture("assets/Button/home.png");
    this->_manager.register_texture("assets/HUD/hud_Life.png");
    this->_manager.register_texture("assets/HUD/Life.png");
    this->_manager.register_texture("assets/Boss/boss1.png");
    this->_manager.register_texture("assets/background/bkgd_1.png");
    this->_manager.register_texture("assets/background/bkgd_2.png");
    this->_manager.register_texture("assets/Power-up/boost_attack_speed.png");
    this->_manager.register_texture("assets/Power-up/boost_attack.png");
    this->_manager.register_texture("assets/Power-up/boost_hp.png");
    this->_manager.register_texture("assets/Power-up/boost_speed.png");
    this->_manager.register_texture("assets/Power-up/boost_double.png");
}

void World::register_menu_assets()
{
    this->_manager.register_texture("assets/background/menu.jpg");
    this->_manager.register_texture("assets/background/bg-boutton.png");
}

void World::register_lobby_assets()
{
    this->_manager.register_texture("assets/background/lobby.png");
    this->_manager.register_texture("assets/background/bg-boutton.png");
    this->_manager.register_texture("assets/SpaceShip/ship_armored_spritesheet.png");
    this->_manager.register_texture("assets/SpaceShip/ship_damage_spritesheet.png");
    this->_manager.register_texture("assets/SpaceShip/ship_engineer_spritesheet.png");
    this->_manager.register_texture("assets/SpaceShip/ship_sniper_spritesheet.png");
}

void World::register_game_assets()
{
    this->_manager.register_texture("assets/r-typesheet1.gif");
    this->_manager.register_texture("assets/r-typesheet5.gif");
    this->_manager.register_texture("assets/r-typesheet39.gif");
    this->_manager.register_texture("assets/SpaceShip/ship_armored_spritesheet.png");
    this->_manager.register_texture("assets/SpaceShip/ship_damage_spritesheet.png");
    this->_manager.register_texture("assets/SpaceShip/ship_engineer_spritesheet.png");
    this->_manager.register_texture("assets/SpaceShip/ship_sniper_spritesheet.png");
    this->_manager.register_texture("assets/SpaceShip/enemy_focus.png");
    this->_manager.register_texture("assets/SpaceShip/enemy_kamikaze.png");
    this->_manager.register_texture("assets/SpaceShip/enemy_sniper.png");
    this->_manager.register_texture("assets/Stats/attack_speed.png");
    this->_manager.register_texture("assets/Stats/boost_attack.png");
    this->_manager.register_texture("assets/Stats/boost_hp.png");
    this->_manager.register_texture("assets/Stats/speed.png");
    this->_manager.register_texture("assets/Button/home.png");
    this->_manager.register_texture("assets/HUD/hud_Life.png");
    this->_manager.register_texture("assets/HUD/Life.png");
    this->_manager.register_texture("assets/Boss/boss1.png");
    this->_manager.register_texture("assets/background/bkgd_1.png");
    this->_manager.register_texture("assets/background/bkgd_2.png");
    this->_manager.register_texture("assets/background/bg-settings.png");
    this->_manager.register_texture("assets/Power-up/boost_attack.png");
    this->_manager.register_texture("assets/Power-up/boost_attack_speed.png");
    this->_manager.register_texture("assets/Power-up/boost_hp.png");
    this->_manager.register_texture("assets/Power-up/boost_speed.png");
    this->_manager.register_texture("assets/Button/button_volume.png");
    this->_manager.register_texture("assets/Button/button_less_volume.png");
    this->_manager.register_texture("assets/Button/button_more_volume.png");
    this->_manager.register_texture("assets/Power-up/boost_double.png");
}

void World::register_option_assets()
{
    this->_manager.register_texture("assets/Button/home.png");
}

sf::Clock &World::getClock()
{
    return (this->_clock);
}

sf::Music &World::getMusic()
{
    return (this->_music);
}

ResourcesManager &World::getResourcesManager()
{
    return (this->_manager);
}

registry &World::getRegistry()
{
    return (this->_r);
}

Vector2i &World::getDirection()
{
    return (this->_player_direction);
}

void World::setDirection(Vector2i direction)
{
    this->_player_direction = direction;
}

size_t World::create_laser(GameObject object, GameTeam team, Vector2f pos, Vector2i speed, float refresh_time)
{
    Entity ent = this->_r.spawn_entity();

    DrawableComponent drawCompo = this->_drawMap[object];
    this->_r.add_component<DrawableComponent>(
        ent, DrawableComponent(drawCompo.path, drawCompo.rect, drawCompo.color, drawCompo.scale));
    this->_r.add_component<WeaponComponent>(
        ent, WeaponComponent("laser", Vector2i{defaultValues[GameObject::PLAYER].atk, 15}, 200));
    this->_r.add_component<VelocityComponent>(
        ent, VelocityComponent(speed, refresh_time, this->_clock.getElapsedTime().asSeconds()));
    this->_r.add_component<PositionComponent>(ent, PositionComponent(pos));
    this->_r.add_component<HealthComponent>(ent, HealthComponent(defaultValues[object].hp));
    this->_r.add_component<GameObjectComponent>(ent, GameObjectComponent(object));
    this->_r.add_component<GameTeamComponent>(ent, GameTeamComponent(team));
    return (ent.id);
}

size_t World::create_laser_enemy(GameObject object, GameTeam team, Vector2f pos, Vector2i speed, float refresh_time)
{
    Entity ent = this->_r.spawn_entity();

    DrawableComponent drawCompo = this->_drawMap[object];
    this->_r.add_component<DrawableComponent>(
        ent, DrawableComponent(drawCompo.path, drawCompo.rect, drawCompo.color, drawCompo.scale));
    this->_r.add_component<WeaponComponent>(
        ent, WeaponComponent("laser", Vector2i{defaultValues[GameObject::ENEMY_SNIPER].atk, 15}, 200));
    this->_r.add_component<VelocityComponent>(
        ent, VelocityComponent(speed, refresh_time, this->_clock.getElapsedTime().asSeconds()));
    this->_r.add_component<PositionComponent>(ent, PositionComponent(pos));
    this->_r.add_component<HealthComponent>(ent, HealthComponent(defaultValues[object].hp));
    this->_r.add_component<GameObjectComponent>(ent, GameObjectComponent(object));
    this->_r.add_component<GameTeamComponent>(ent, GameTeamComponent(team));
    this->_r.add_component<SoundEffectComponent>(ent, SoundEffectComponent("laser", true));
    return (ent.id);
}

size_t World::create_player(GameObject object, Vector2f pos, Vector2i speed, float refresh_time)
{
    Entity ent = this->_r.spawn_entity();

    DrawableComponent drawCompo = this->_drawMap[object];
    this->_r.add_component<DrawableComponent>(
        ent, DrawableComponent(drawCompo.path, drawCompo.rect, drawCompo.color, drawCompo.scale));
    this->_r.add_component<WeaponComponent>(ent, WeaponComponent("body", Vector2i{defaultValues[object].atk, 15}, 200));
    this->_r.add_component<PositionComponent>(ent, PositionComponent(pos));
    this->_r.add_component<ImmobileComponent>(ent, ImmobileComponent(Vector2b(true, true)));
    this->_r.add_component<DestroyableComponent>(ent, DestroyableComponent(true));
    this->_r.add_component<HealthComponent>(ent, HealthComponent(defaultValues[object].hp));
    this->_r.add_component<VelocityComponent>(
        ent, VelocityComponent(speed, refresh_time, this->_clock.getElapsedTime().asSeconds()));
    this->_r.add_component<GameObjectComponent>(ent, GameObjectComponent(object));
    this->_r.add_component<SpeedComponent>(ent, SpeedComponent(defaultValues[GameObject::PLAYER].spd));
    this->_r.add_component<GameTeamComponent>(ent, GameTeamComponent(GameTeam::PLAYER));
    this->_r.add_component<ControllableComponent>(ent,
        ControllableComponent(
            KeyboardInput::Z, KeyboardInput::S, KeyboardInput::D, KeyboardInput::Q, MouseInput::Left_click));
    this->_r.add_component<DoubleLaserComponent>(ent, DoubleLaserComponent(false));
    this->_r.add_component<LevelComponent>(ent, {0, 0});

    return (ent.id);
}

size_t World::create_enemy(GameObject object, Vector2f pos, Vector2i speed, size_t health, float refresh_time)
{
    Entity ent = this->_r.spawn_entity();

    DrawableComponent drawCompo = this->_drawMap[object];
    this->_r.add_component<DrawableComponent>(
        ent, DrawableComponent(drawCompo.path, drawCompo.rect, drawCompo.color, drawCompo.scale));
    this->_r.add_component<PositionComponent>(ent, PositionComponent(pos));
    this->_r.add_component<ImmobileComponent>(ent, ImmobileComponent(Vector2b(false, false)));
    this->_r.add_component<CollideComponent>(ent, CollideComponent());
    this->_r.add_component<WeaponComponent>(ent, WeaponComponent("meteor", Vector2i{defaultValues[object].atk, 1}, 0));
    this->_r.add_component<DestroyableComponent>(ent, DestroyableComponent(true));
    this->_r.add_component<HealthComponent>(ent, HealthComponent(health));
    this->_r.add_component<GameObjectComponent>(ent, GameObjectComponent(object));
    this->_r.add_component<VelocityComponent>(
        ent, VelocityComponent(speed, refresh_time, this->_clock.getElapsedTime().asSeconds()));
    this->_r.add_component<GameTeamComponent>(ent, GameTeamComponent(GameTeam::ENEMY));
    this->_r.add_component<SoundEffectComponent>(ent, SoundEffectComponent("explosion", true));

    return (ent.id);
}

size_t World::create_bonus(GameObject object, Vector2f pos, Vector2i speed, float refresh_time, Bonus bonusName)
{
    Entity ent = this->_r.spawn_entity();

    DrawableComponent drawCompo = this->_drawMap[object];
    this->_r.add_component<DrawableComponent>(
        ent, DrawableComponent(drawCompo.path, drawCompo.rect, Vector4i{255, 255, 255, 255}, drawCompo.scale));
    this->_r.add_component<PositionComponent>(ent, PositionComponent(pos));
    this->_r.add_component<ImmobileComponent>(ent, ImmobileComponent(Vector2b(false, false)));
    this->_r.add_component<DestroyableComponent>(ent, DestroyableComponent(true));
    this->_r.add_component<HealthComponent>(ent, HealthComponent(100));
    this->_r.add_component<VelocityComponent>(
        ent, VelocityComponent(speed, refresh_time, this->_clock.getElapsedTime().asSeconds()));
    this->_r.add_component<BonusComponent>(ent, BonusComponent(bonusName, std::chrono::steady_clock::now()));
    this->_r.add_component<GameTeamComponent>(ent, GameTeamComponent(GameTeam::NEUTRAL));
    this->_r.add_component<SoundEffectComponent>(ent, SoundEffectComponent("bonus", true));
    return (ent.id);
}

size_t World::create_drawable_object(std::string asset_path, Vector4i rect, Vector4i color, Vector2f scale,
    Vector2f pos, Vector2i speed, float refresh_time)
{
    Entity ent = this->_r.spawn_entity();

    this->_r.add_component<DrawableComponent>(ent, DrawableComponent(asset_path, rect, color, scale));
    this->_r.add_component<PositionComponent>(ent, PositionComponent(pos));
    this->_r.add_component<HealthComponent>(ent, (HealthComponent(1)));
    if (speed.x != 0 || speed.y != 0)
        this->_r.add_component<VelocityComponent>(
            ent, VelocityComponent(speed, refresh_time, this->_clock.getElapsedTime().asSeconds()));
    this->_r.add_component<GameTeamComponent>(ent, GameTeamComponent(GameTeam::NONE));

    return (ent.id);
}

size_t World::create_text(std::string text, std::string font, int size, Vector2f pos)
{
    Entity ent = this->_r.spawn_entity();

    this->_r.add_component<TextComponent>(ent, TextComponent(text, font, size));
    this->_r.add_component<PositionComponent>(ent, PositionComponent(pos));
    this->_r.add_component<GameTeamComponent>(ent, GameTeamComponent(GameTeam::NONE));

    return (ent.id);
}

size_t World::create_button(std::string asset, Vector4i rect, Vector4i color, Vector2f scale, Vector2f pos,
    std::function<void(World &, SceneScreen &, NetworkClient &, float &)> callback)
{
    size_t id = this->create_drawable_object(asset, rect, color, scale, pos);
    this->_r.add_component((Entity)id, ClickableComponent(callback));
    return (id);
}

void World::create_skills(Vector2f pos)
{
    Entity ent = this->_r.spawn_entity();

    this->_r.add_component<DrawableComponent>(ent,
        DrawableComponent("assets/Stats/boost_attack.png", Vector4i{0, 0, 1075, 1027}, Vector4i{255, 255, 255, 255},
            Vector2f{0.05, 0.05}));
    this->_r.add_component<PositionComponent>(ent, PositionComponent({pos.x / 2 - 100, pos.y - 50}));
    this->_r.add_component<HealthComponent>(ent, (HealthComponent(1)));

    Entity ent2 = this->_r.spawn_entity();

    this->_r.add_component<DrawableComponent>(ent2,
        DrawableComponent("assets/Stats/attack_speed.png", Vector4i{0, 0, 1075, 1027}, Vector4i{255, 255, 255, 255},
            Vector2f{0.05, 0.05}));
    this->_r.add_component<PositionComponent>(ent2, PositionComponent({pos.x / 2 - 53, pos.y - 50}));
    this->_r.add_component<HealthComponent>(ent2, (HealthComponent(1)));

    Entity ent3 = this->_r.spawn_entity();

    this->_r.add_component<DrawableComponent>(ent3,
        DrawableComponent("assets/Stats/boost_hp.png", Vector4i{0, 0, 1075, 1027}, Vector4i{255, 255, 255, 255},
            Vector2f{0.05, 0.05}));
    this->_r.add_component<PositionComponent>(ent3, PositionComponent({pos.x / 2 - 6, pos.y - 50}));
    this->_r.add_component<HealthComponent>(ent3, (HealthComponent(1)));

    Entity ent4 = this->_r.spawn_entity();

    this->_r.add_component<DrawableComponent>(ent4,
        DrawableComponent(
            "assets/Stats/speed.png", Vector4i{0, 0, 1075, 1027}, Vector4i{255, 255, 255, 255}, Vector2f{0.05, 0.05}));
    this->_r.add_component<PositionComponent>(ent4, PositionComponent({pos.x / 2 + 41, pos.y - 50}));
    this->_r.add_component<HealthComponent>(ent4, (HealthComponent(1)));
}

void World::create_settings(Vector2f pos)
{
    Entity ent = this->_r.spawn_entity();

    this->_r.add_component<DrawableComponent>(ent,
        DrawableComponent(
            "assets/Button/home.png", Vector4i{0, 0, 319, 319}, Vector4i{255, 255, 255, 255}, Vector2f{0.1, 0.1}));
    this->_r.add_component<PositionComponent>(ent, PositionComponent({pos.x - 32, 0}));
    this->_r.add_component<HealthComponent>(ent, (HealthComponent(1)));
}

void World::create_healthbar(float life)
{
    Entity ent = this->_r.spawn_entity();

    this->_r.add_component<DrawableComponent>(ent,
        DrawableComponent(
            "assets/HUD/hud_Life.png", Vector4i{0, 0, 1074, 402}, Vector4i{255, 255, 255, 255}, Vector2f{0.1, 0.1}));
    this->_r.add_component<PositionComponent>(ent, PositionComponent({0, 0}));
    this->_r.add_component<HealthComponent>(ent, (HealthComponent(1)));

    Entity ent2 = this->_r.spawn_entity();

    this->_r.add_component<DrawableComponent>(ent2,
        DrawableComponent("assets/HUD/Life.png", Vector4i{0, 0, (int)(674 * life), 53}, Vector4i{255, 255, 255, 255},
            Vector2f{0.1, 0.1}));
    this->_r.add_component<PositionComponent>(ent2, PositionComponent({33, 23}));
    this->_r.add_component<HealthComponent>(ent2, (HealthComponent(1)));
}

void World::create_border_entities()
{
    Entity player_border = this->_r.spawn_entity();

    this->_r.add_component<DrawableComponent>(
        player_border, DrawableComponent("assets/background/menu.jpg", Vector4i{0, 0, 1, 1080}));
    this->_r.add_component<PositionComponent>(player_border, PositionComponent({2200, 0}));
    this->_r.add_component<HealthComponent>(player_border, (HealthComponent(99999999)));
    this->_r.add_component<WeaponComponent>(player_border, WeaponComponent("meteor", Vector2i{99999, 1}, 0));
    this->_r.add_component<DestroyableComponent>(player_border, DestroyableComponent(true));
    this->_r.add_component<GameTeamComponent>(player_border, GameTeamComponent(GameTeam::NONE));
    this->_r.add_component<EntityIDComponent>(player_border, EntityIDComponent((size_t)player_border));

    Entity enemy_border = this->_r.spawn_entity();

    this->_r.add_component<DrawableComponent>(
        enemy_border, DrawableComponent("assets/background/menu.jpg", Vector4i{0, 0, 1, 1080}));
    this->_r.add_component<PositionComponent>(enemy_border, PositionComponent({-500, 0}));
    this->_r.add_component<HealthComponent>(enemy_border, (HealthComponent(99999999)));
    this->_r.add_component<WeaponComponent>(enemy_border, WeaponComponent("meteor", Vector2i{99999, 1}, 0));
    this->_r.add_component<DestroyableComponent>(enemy_border, DestroyableComponent(true));
    this->_r.add_component<GameTeamComponent>(enemy_border, GameTeamComponent(GameTeam::PLAYER));
    this->_r.add_component<EntityIDComponent>(enemy_border, EntityIDComponent((size_t)enemy_border));
}

void World::register_all_drawable_object()
{
    this->_drawMap.emplace(GameObject::BOSS_1,
        DrawableComponent("assets/Boss/boss1.png", Vector4i{0, 0, 245, 245}, Vector4i{255, 255, 255, 255},
            Vector2f{defaultValues[GameObject::BOSS_1].scale, defaultValues[GameObject::BOSS_1].scale}));
    this->_drawMap.emplace(GameObject::LASER, DrawableComponent("assets/r-typesheet1.gif", Vector4i(104, 171, 80, 14)));
    this->_drawMap.emplace(GameObject::LASER_ENEMY,
        DrawableComponent("assets/r-typesheet1.gif", Vector4i(104, 171, 80, 14), Vector4i{255, 255, 255, 255},
            Vector2f{defaultValues[GameObject::LASER_ENEMY].scale, defaultValues[GameObject::LASER_ENEMY].scale}));
    this->_drawMap.emplace(GameObject::PLAYER,
        DrawableComponent("assets/r-typesheet5.gif", Vector4i{375, 6, 21, 24}, Vector4i{255, 255, 255, 255},
            Vector2f{defaultValues[GameObject::PLAYER].scale, defaultValues[GameObject::PLAYER].scale}));
    this->_drawMap.emplace(GameObject::ENEMY_FOCUS,
        DrawableComponent("assets/SpaceShip/enemy_focus.png", Vector4i{0, 0, 112, 98}, Vector4i{255, 255, 255, 255},
            Vector2f{defaultValues[GameObject::ENEMY_FOCUS].scale, defaultValues[GameObject::ENEMY_FOCUS].scale}));
    this->_drawMap.emplace(GameObject::ENEMY_KAMIKAZE,
        DrawableComponent("assets/SpaceShip/enemy_kamikaze.png", Vector4i{0, 0, 80, 79}, Vector4i{255, 255, 255, 255},
            Vector2f{
                defaultValues[GameObject::ENEMY_KAMIKAZE].scale, defaultValues[GameObject::ENEMY_KAMIKAZE].scale}));
    this->_drawMap.emplace(GameObject::ENEMY_SNIPER,
        DrawableComponent("assets/SpaceShip/enemy_sniper.png", Vector4i{0, 0, 156, 83}, Vector4i{255, 255, 255, 255},
            Vector2f{defaultValues[GameObject::ENEMY_SNIPER].scale, defaultValues[GameObject::ENEMY_SNIPER].scale}));
    this->_drawMap.emplace(GameObject::BOSS_1,
        DrawableComponent(
            "assets/Boss/boss1.png", Vector4i{0, 0, 245, 245}, Vector4i{255, 255, 255, 255}, Vector2f{1.0, 1.0}));
    this->_drawMap.emplace(GameObject::BONUS_ATTACK,
        DrawableComponent("assets/Power-up/boost_attack.png", Vector4i{0, 0, 512, 494}, Vector4i{255, 255, 255, 255},
            Vector2f{0.08, 0.08}));
    this->_drawMap.emplace(GameObject::BONUS_ATTACK_SPEED,
        DrawableComponent("assets/Power-up/boost_attack_speed.png", Vector4i{0, 0, 512, 494},
            Vector4i{255, 255, 255, 255}, Vector2f{0.08, 0.08}));
    this->_drawMap.emplace(GameObject::BONUS_HEAL,
        DrawableComponent("assets/Power-up/boost_hp.png", Vector4i{0, 0, 512, 512}, Vector4i{255, 255, 255, 255},
            Vector2f{0.08, 0.08}));
    this->_drawMap.emplace(GameObject::BONUS_SPEED,
        DrawableComponent("assets/Power-up/boost_speed.png", Vector4i{0, 0, 512, 494}, Vector4i{255, 255, 255, 255},
            Vector2f{0.08, 0.08}));
    this->_drawMap.emplace(GameObject::BONUS_DOUBLE,
        DrawableComponent("assets/Power-up/boost_double.png", Vector4i{0, 0, 512, 494}, Vector4i{255, 255, 255, 255},
            Vector2f{0.08, 0.08}));
    this->_drawMap.emplace(GameObject::SHIP_ARMORED,
        DrawableComponent("assets/SpaceShip/ship_armored_spritesheet.png", Vector4i{0, 0, 128, 128},
            Vector4i{255, 255, 255, 255},
            Vector2f{defaultValues[GameObject::SHIP_ARMORED].scale, defaultValues[GameObject::SHIP_ARMORED].scale}));
    this->_drawMap.emplace(GameObject::SHIP_DAMAGE,
        DrawableComponent("assets/SpaceShip/ship_damage_spritesheet.png", Vector4i{0, 0, 128, 128},
            Vector4i{255, 255, 255, 255},
            Vector2f{defaultValues[GameObject::SHIP_DAMAGE].scale, defaultValues[GameObject::SHIP_DAMAGE].scale}));
    this->_drawMap.emplace(GameObject::SHIP_ENGINEER,
        DrawableComponent("assets/SpaceShip/ship_engineer_spritesheet.png", Vector4i{0, 0, 128, 128},
            Vector4i{255, 255, 255, 255},
            Vector2f{defaultValues[GameObject::SHIP_ENGINEER].scale, defaultValues[GameObject::SHIP_ENGINEER].scale}));
    this->_drawMap.emplace(GameObject::SHIP_SNIPER,
        DrawableComponent("assets/SpaceShip/ship_sniper_spritesheet.png", Vector4i{0, 0, 128, 128},
            Vector4i{255, 255, 255, 255},
            Vector2f{defaultValues[GameObject::SHIP_SNIPER].scale, defaultValues[GameObject::SHIP_SNIPER].scale}));
}
