/**
 * @file client.cpp
 * @author Tanguy Bellicha (tanguy.bellicha@epitech.eu)
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
    NetworkClient::Send("");
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

void NetworkClient::Send(const std::string &message)
{
    socket.send_to(boost::asio::buffer(message), server_endpoint);
}

#include <iostream>

void NetworkClient::SendMessage(const Message<GameMessage> &message)
{
    std::cout << message.size() << std::endl;

    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string>> s(inserter);
    boost::archive::binary_oarchive oa(s);

    oa << message;

    s.flush();

    Send(serial_str);
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
    Vector2i pos;

    msg >> object >> pos;
    PositionComponent position(pos);
    if (object == GameObject::PLAYER) {
        world.create_player(GameObject::PLAYER, position.pos, Vector2i(5, 5), 0.2);
    }
    if (object == GameObject::ENEMY) {
        world.create_enemy(GameObject::ENEMY, position.pos, Vector2i(10, 0), 0.2, world.getClock().getElapsedTime().asSeconds());
    }
    if (object == GameObject::LASER) {
        world.create_laser(GameObject::LASER, position.pos, Vector2i(15, 0), 0.04, world.getClock().getElapsedTime().asSeconds());
    }
}

static std::map<GameMessage, std::function<void(World &, Message<GameMessage>)>> mapFunc =
{
    {GameMessage::S2C_ENTITY_NEW, new_entity},
};

void NetworkClient::processMessage(Message<GameMessage> &msg, World &world)
{
    (mapFunc[msg.header.id])(world, msg);
}