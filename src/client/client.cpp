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

static std::map<GameObject, std::function<void(World &, size_t, Vector2f)>> newEntity = {
    {GameObject::PLAYER, new_player},
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
 */
void new_entity(World &world, Message<GameMessage> msg)
{
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
 */
void dead_entity(World &world, Message<GameMessage> msg)
{
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
 * @param world The world to update
 * @param msg The message containing data
 */
void game_end(World &world, Message<GameMessage> msg)
{
    world.getWindow().close();
    (void)msg;
}

/**
 * @brief Act on a movement
 *
 * @param world The world to update
 * @param msg The message containing data
 */
void movement(World &world, Message<GameMessage> msg)
{
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
 */
void entity_hit(World &world, Message<GameMessage> msg)
{
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
 */
void ok_packet(World &world, Message<GameMessage> msg)
{
    (void)world;
    (void)msg;
    // ok j'en fais quoi ???
}

/**
 * @brief Update a wave
 *
 * @param world The world to update
 * @param msg The message containing data
 */
void wave_status(World &world, Message<GameMessage> msg)
{
    size_t nb_wave = 0;
    WaveStatus status;
    (void)world;

    msg >> nb_wave;
    msg >> status;

    switch (status) {
        case WaveStatus::START: std::cout << "Wave " << nb_wave << " is starting" << std::endl; break;
        case WaveStatus::BOSS_START: std::cout << "Boss wave " << nb_wave << " is starting" << std::endl; break;
        case WaveStatus::END: std::cout << "Wave " << nb_wave << " ended" << std::endl; break;
    }
}

static std::map<GameMessage, std::function<void(World &, Message<GameMessage>)>> mapFunc = {
    {GameMessage::S2C_ENTITY_NEW, new_entity},
    {GameMessage::S2C_ENTITY_DEAD, dead_entity},
    {GameMessage::S2C_GAME_END, game_end},
    {GameMessage::S2C_MOVEMENT, movement},
    {GameMessage::S2C_ENTITY_HIT, entity_hit},
    {GameMessage::S2C_WAVE_STATUS, wave_status},
    {GameMessage::S2C_OK, ok_packet},
};

void NetworkClient::processMessage(Message<GameMessage> &msg, World &world)
{
    mapFunc[msg.header.id](world, msg);
}
