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

void new_entity(World &world, Message<GameMessage> msg)
{
    GameObject object;
    Vector2f pos;
    size_t srv_entity_id;
    size_t new_entity_id;

    msg >> pos >> srv_entity_id >> object;
    PositionComponent position(pos);
    if (object == GameObject::PLAYER) {
        new_entity_id = world.create_player(GameObject::PLAYER, position.pos, Vector2i{0, 0}, 0.2f);
        world.getRegistry().add_component<EntityIDComponent>(
            world.getRegistry().entity_from_index(new_entity_id), EntityIDComponent{srv_entity_id});
        std::cout << "Player[" << srv_entity_id << "]: joined the game at (" << pos.x << ", " << pos.y << ")"
                  << std::endl;
        return;
    }
    if (object == GameObject::ENEMY) {
        new_entity_id = world.create_enemy(
            GameObject::ENEMY, position.pos, Vector2i{0, 0}, 0.2f, world.getClock().getElapsedTime().asSeconds());
        world.getRegistry().add_component<EntityIDComponent>(
            world.getRegistry().entity_from_index(new_entity_id), EntityIDComponent{srv_entity_id});
        std::cout << "Enemy[" << srv_entity_id << "]: spawned at (" << pos.x << ", " << pos.y << ")" << std::endl;
        return;
    }
    if (object == GameObject::LASER) {
        new_entity_id = world.create_laser(
            GameObject::LASER, position.pos, Vector2i{0, 0}, 0.04f, world.getClock().getElapsedTime().asSeconds());
        world.getRegistry().add_component<EntityIDComponent>(
            world.getRegistry().entity_from_index(new_entity_id), EntityIDComponent{srv_entity_id});
        std::cout << "Laser[" << srv_entity_id << "]: spawned at (" << pos.x << ", " << pos.y << ")" << std::endl;
        return;
    }
    std::cout << "Unknown object type" << std::endl;
}

void dead_entity(World &world, Message<GameMessage> msg)
{
    ClientIDComponent id_entity;

    msg >> id_entity;
    world.getRegistry().kill_entity(world.getRegistry().entity_from_index(id_entity.id));
}

void game_end(World &world, Message<GameMessage> msg)
{
    world.getWindow().close();
}

void movement(World &world, Message<GameMessage> msg)
{
    registry &r = world.getRegistry();
    ClientIDComponent moved_id;
    Vector2i velocity;

    msg >> velocity >> moved_id;
    auto &velocityCompo = r.get_components<VelocityComponent>();

    if (velocityCompo[moved_id.id] && velocityCompo[moved_id.id].has_value()) {
        std::cout << "Player[" << moved_id.id << "]: Velocity{" << velocity.x << ", " << velocity.y << "}" << std::endl;
        velocityCompo[moved_id.id]->speed.x = velocity.x;
        velocityCompo[moved_id.id]->speed.y = velocity.y;
    }
}

void player_hit(World &world, Message<GameMessage> msg)
{
    registry &r = world.getRegistry();
    ClientIDComponent hitted_id;
    int damage;

    msg >> damage >> hitted_id;

    auto &health = r.get_components<HealthComponent>();

    if (health[hitted_id.id] && health[hitted_id.id].has_value())
        health[hitted_id.id]->hp -= damage;
}

void ok_packet(World &world, Message<GameMessage> msg)
{
    // ok j'en fais quoi ???
}

static std::map<GameMessage, std::function<void(World &, Message<GameMessage>)>> mapFunc = {
    {GameMessage::S2C_ENTITY_NEW, new_entity},
    {GameMessage::S2C_ENTITY_DEAD, dead_entity},
    {GameMessage::S2C_GAME_END, game_end},
    {GameMessage::S2C_MOVEMENT, movement},
    {GameMessage::S2C_PLAYER_HIT, player_hit},
    {GameMessage::S2C_OK, ok_packet},
};

void NetworkClient::processMessage(Message<GameMessage> &msg, World &world)
{
    (mapFunc[msg.header.id])(world, msg);
}