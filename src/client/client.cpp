/**
 * @file client.cpp
 * @author Adam Djebar (adam.djebar@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-10-16
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "client.hpp"
#include <boost/iostreams/stream.hpp>
#include <boost/serialization/vector.hpp>
#include <sstream>
#include "proto.hpp"
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/iostreams/device/back_inserter.hpp>

NetworkClient::NetworkClient(std::string host, std::string server_port, unsigned short local_port)
    : socket(io_service, udp::endpoint(udp::v4(), local_port)), service_thread(&NetworkClient::run_service, this)
{
    this->_nb_players = 0;
    this->_players_ready = false;
    this->_launch_game = false;
    udp::resolver resolver(io_service);
    udp::resolver::query query(udp::v4(), host, server_port);
    server_endpoint = *resolver.resolve(query);
    NetworkClient::send("");
}

NetworkClient::~NetworkClient()
{
    io_service.stop();
    service_thread.join();
}

void NetworkClient::start_receive()
{
    socket.async_receive_from(
        boost::asio::buffer(recv_buffer), remote_endpoint, [this](std::error_code ec, std::size_t bytes_recvd) {
            this->handle_receive(ec, bytes_recvd);
        });
}

void NetworkClient::handle_receive(const std::error_code &error, std::size_t bytes_transferred)
{
    if (!error) {
        try {
            Message<GameMessage> gameMsg;

            std::string recv_str(recv_buffer.data(), recv_buffer.data() + bytes_transferred);

            boost::iostreams::basic_array_source<char> device(recv_str.data(), recv_str.size());
            boost::iostreams::stream<boost::iostreams::basic_array_source<char>> s(device);
            boost::archive::binary_iarchive ia(s);
            ia >> gameMsg;

            // std::cout << gameMsg.body

            if (gameMsg.size() != 0)
                incomingMessages.push(gameMsg);
        } catch (...) {
        }
    } else {
    }

    start_receive();
}

void NetworkClient::send(const std::string &message)
{
    socket.send_to(boost::asio::buffer(message), server_endpoint);
}

void NetworkClient::send(const Message<GameMessage> &message)
{
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string>> s(inserter);
    boost::archive::binary_oarchive oa(s);

    oa << message;
    s.flush();
    send(serial_str);
}

bool NetworkClient::HasMessages()
{
    return !incomingMessages.empty();
}

Message<GameMessage> NetworkClient::PopMessage()
{
    if (incomingMessages.empty())
        throw std::logic_error("No messages to pop");
    return incomingMessages.pop();
}

void NetworkClient::run_service()
{
    start_receive();
    while (!io_service.stopped()) {
        try {
            io_service.run();
        } catch (const std::exception &e) {
        } catch (...) {
        }
    }
}

void NetworkClient::set_launch_game(bool launch)
{
    this->_launch_game = launch;
}

bool NetworkClient::get_launch_game() const
{
    return (this->_launch_game);
}

void NetworkClient::set_players_ready(bool ready)
{
    this->_players_ready = ready;
}

bool NetworkClient::get_players_ready() const
{
    return (this->_players_ready);
}

void NetworkClient::set_nb_players(int nb_players)
{
    this->_nb_players = nb_players;
}

int NetworkClient::get_nb_players() const
{
    return (_nb_players);
}

static std::map<GameObject, std::function<void(World &, size_t, Vector2f)>> newEntity = {
    {GameObject::PLAYER, new_player},
    {GameObject::SHIP_ARMORED, new_armored_player},
    {GameObject::SHIP_DAMAGE, new_damage_player},
    {GameObject::SHIP_ENGINEER, new_engineer_player},
    {GameObject::SHIP_SNIPER, new_sniper_player},
    {GameObject::BOSS_1, new_boss1},
    {GameObject::ENEMY_FOCUS, new_enemy_focus},
    {GameObject::ENEMY_SNIPER, new_enemy_sniper},
    {GameObject::ENEMY_ODD, new_enemy_odd},
    {GameObject::LASER, new_laser},
};

/**
 * @brief Create a new entity
 *
 * @param world The world to add the entity to
 * @param msg The message containing the entity data
 * @param client The client to update
 * @param current_screen The current screen
 */
void new_entity(World &world, NetworkClient &client, Message<GameMessage> msg, SceneScreen &current_screen)
{
    (void)client;
    (void)current_screen;
    Vector2f pos;
    size_t srv_entity_id;
    GameObject object;

    msg >> pos >> srv_entity_id >> object;
    newEntity[object](world, srv_entity_id, pos);
}

/**
 * @brief Update an entity that has died
 *
 * @param world The world to update
 * @param msg The message containing the entity data
 * @param client The client to update
 * @param current_screen The current screen
 */
void dead_entity(World &world, NetworkClient &client, Message<GameMessage> msg, SceneScreen &current_screen)
{
    (void)client;
    (void)current_screen;
    EntityIDComponent id_entity;
    auto &entityIdCompo = world.getRegistry().get_components<EntityIDComponent>();
    size_t index = 0;

    msg >> id_entity;
    for (auto &entityId : entityIdCompo) {
        if (entityId && entityId.has_value()) {
            if (entityId->id == id_entity.id) {
                std::cout << "Entity[" << id_entity.id << "] was destroyed" << std::endl;
                world.getRegistry().kill_entity(world.getRegistry().entity_from_index(index));
                break;
            }
        }
        index++;
    }
}

/**
 * @brief End the game
 *
 * @param window The window to close
 */
void game_end(sf::RenderWindow &window)
{
    window.close();
}

/**
 * @brief Act on a movement
 *
 * @param world The world to update
 * @param msg The message containing data
 * @param client The client to update
 * @param current_screen The current screen
 */
void movement(World &world, NetworkClient &client, Message<GameMessage> msg, SceneScreen &current_screen)
{
    (void)client;
    (void)current_screen;
    registry &r = world.getRegistry();
    auto &velocityCompo = r.get_components<VelocityComponent>();
    auto &entityId = r.get_components<EntityIDComponent>();
    EntityIDComponent moved_id;
    Vector2i velocity = {0, 0};
    size_t index = 0;

    msg >> velocity >> moved_id;
    for (auto &idCompo : entityId) {
        if (idCompo && idCompo.has_value()) {
            if (idCompo->id == moved_id.id) {
                std::cout << "Entity[" << moved_id.id << "]: Velocity{" << velocity.x << ", " << velocity.y << "}"
                          << std::endl;
                velocityCompo[index]->speed.x = velocity.x;
                velocityCompo[index]->speed.y = velocity.y;
                break;
            }
        }
        index++;
    }
}

/**
 * @brief Hit an entity
 *
 * @param world The world to update
 * @param msg The message containing data
 * @param client The client to update
 * @param current_screen The current screen
 */
void entity_hit(World &world, NetworkClient &client, Message<GameMessage> msg, SceneScreen &current_screen)
{
    (void)client;
    (void)current_screen;
    registry &r = world.getRegistry();
    ClientIDComponent hit_id;
    int damage = 0;
    size_t max_hp = 0;

    msg >> max_hp >> damage >> hit_id;

    auto &health = r.get_components<HealthComponent>();
    auto &entityIdCompo = r.get_components<EntityIDComponent>();

    size_t index = 0;

    for (auto &idCompo : entityIdCompo) {
        if (idCompo && idCompo.has_value()) {
            if (idCompo->id == hit_id.id) {
                health[index]->hp -= damage;
                health[index]->max_hp = max_hp;
                std::cout << "Entity[" << hit_id.id << "]: -" << damage << "HP, now has " << health[index]->hp << "/"
                          << max_hp << "HP" << std::endl;
                break;
            }
        }
        index++;
    }
}

/**
 * @brief Validate a packet
 *
 * @param world The world to update
 * @param msg The message containing data
 * @param client The client to update
 * @param current_screen The current screen
 */
void ok_packet(World &world, NetworkClient &client, Message<GameMessage> msg, SceneScreen &current_screen)
{
    (void)world;
    (void)client;
    (void)msg;
    (void)current_screen;
    // ok j'en fais quoi ???
}

/**
 * @brief Log the status of the wave
 *
 * @param world The world to update
 * @param msg The message containing data
 * @param client The client to update
 * @param current_screen The current screen
 */
void wave_status(World &world, NetworkClient &client, Message<GameMessage> msg, SceneScreen &current_screen)
{
    size_t nb_wave = 0;
    WaveStatus status;
    (void)world;
    (void)client;
    (void)current_screen;

    msg >> nb_wave;
    msg >> status;

    switch (status) {
        case WaveStatus::START: std::cout << "Wave " << nb_wave << " is starting" << std::endl; break;
        case WaveStatus::BOSS_START: std::cout << "Boss wave " << nb_wave << " is starting" << std::endl; break;
        case WaveStatus::END: std::cout << "Wave " << nb_wave << " ended" << std::endl; break;
    }
}

/**
 * @brief Set the number of players
 *
 * @param world The world to update
 * @param msg The message containing data
 * @param client The client to update
 * @param current_screen The current screen
 */
void players_numbers(World &world, NetworkClient &client, Message<GameMessage> msg, SceneScreen &current_screen)
{
    (void)world;
    (void)current_screen;
    std::size_t nb_players;

    msg >> nb_players;
    client.set_nb_players((int)nb_players);
}

/**
 * @brief Change scene to go to the screen game
 *
 * @param world The world to update
 * @param msg The message containing data
 * @param client The client to update
 * @param current_screen The current screen
 */
void game_start(World &world, NetworkClient &client, Message<GameMessage> msg, SceneScreen &current_screen)
{
    (void)world;
    (void)msg;
    (void)client;
    current_screen = SceneScreen::GAME;
}

/**
 * @brief Set the player to ready state
 *
 * @param world The world to update
 * @param msg The message containing data
 * @param client The client to update
 * @param current_screen The current screen
 */
void players_ready(World &world, NetworkClient &client, Message<GameMessage> msg, SceneScreen &current_screen)
{
    (void)world;
    (void)current_screen;
    bool ready;

    msg >> ready;
    client.set_players_ready(ready);
}

void update_position(World &world, NetworkClient &client, Message<GameMessage> msg, SceneScreen &current_scene)
{
    (void)client;
    (void)current_scene;
    registry &r = world.getRegistry();
    ClientIDComponent entity_id;
    PositionComponent pos({0, 0});

    std::cout << "bro" << std::endl;
    msg >> entity_id >> pos;

    auto &entityIdCompo = r.get_components<EntityIDComponent>();
    auto &posCompo = r.get_components<PositionComponent>();

    size_t index = 0;

    for (auto &idCompo : entityIdCompo) {
        if (idCompo && idCompo.has_value()) {
            if (!(posCompo[index] && posCompo[index].has_value()))
                break;
            if (idCompo->id == entity_id.id) {
                posCompo[index] = pos;
                std::cout << "Entity[" << entity_id.id << "]: at {" << posCompo[index]->pos.x << ", " << posCompo[index]->pos.y << "}" << std::endl;
                break;
            }
        }
        index++;
    }
}

static std::map<GameMessage, std::function<void(World &, NetworkClient &, Message<GameMessage>, SceneScreen &)>>
    mapFunc = {{GameMessage::S2C_ENTITY_NEW, new_entity}, {GameMessage::S2C_ENTITY_DEAD, dead_entity},
        {GameMessage::S2C_MOVEMENT, movement}, {GameMessage::S2C_ENTITY_HIT, entity_hit},
        {GameMessage::S2C_WAVE_STATUS, wave_status}, {GameMessage::S2C_OK, ok_packet},
        {GameMessage::S2C_START_GAME, game_start}, {GameMessage::S2C_PLAYERS_READY, players_ready},
        {GameMessage::S2C_PLAYERS_IN_LOBBY, players_numbers}, {GameMessage::S2C_UPDATE_POSITION, update_position}};

void NetworkClient::processMessage(
    Message<GameMessage> &msg, World &world, sf::RenderWindow &window, SceneScreen &screen)
{
    (mapFunc[msg.header.id])(world, *this, msg, screen);
    if (msg.header.id == GameMessage::S2C_GAME_END) {
        game_end(window);
    }
}
