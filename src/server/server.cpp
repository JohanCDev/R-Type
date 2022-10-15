/**
 * @file server.cpp
 * @author Louis Maestre (louis.maestre@epitech.eu)
 * @brief udp server creation
 * @version 0.1
 * @date 2022-10-05
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <functional>
#include <map>

#include "Package/IPackage.hpp"
#include "server.hpp"
#include "Package/Packets/S2C_EntityDead.hpp"
#include "Package/Packets/S2C_EntityHit.hpp"
#include "Package/Packets/S2C_EntityNew.hpp"
#include "Package/Packets/S2C_Error.hpp"
#include "Package/Packets/S2C_GameEnd.hpp"
#include "Package/Packets/S2C_Movement.hpp"
#include "Package/Packets/S2C_Ok.hpp"

std::string udp_server::deserialize(std::string recv)
{
    for (int i = 0; i < recv.size(); i++) {
        recv[i] = ((unsigned char)recv[i]) >> 1;
    }
    return (recv);
}

std::string udp_server::serialize(std::string recv)
{
    for (int i = 0; i < recv.size(); i++) {
        recv[i] = ((unsigned char)recv[i]) << 1;
    }
    return (recv);
}

void udp_server::getData(boost::array<char, 64> recv_buffer)
{
    std::string recv = recv_buffer.data();
    std::string serialization_res = serialize(recv);
    std::istringstream tmp(recv_buffer.data());
    std::string arg1;
    std::string size;
    std::string desc = recv_buffer.data();

    S2C_OK _ok;
    S2C_ERROR _error;
    S2C_MOVEMENT _mvt;
    S2C_ENTITY_NEW _newEntity;
    S2C_ENTITY_DEAD _deadEntity;
    S2C_ENTITY_HIT _hitEntity;
    S2C_GAME_END _endGame;
    std::map<std::string, std::function<void()>> mapFunc;

    tmp >> arg1 >> size;
    mapFunc["S2C_OK"] = std::bind(&S2C_OK::send, _ok);
    mapFunc["S2C_ERROR"] = std::bind(&S2C_ERROR::send, _error);
    mapFunc["S2C_MOVEMENT"] = std::bind(&S2C_MOVEMENT::send, _mvt);
    mapFunc["S2C_ENTITY_NEW"] = std::bind(&S2C_ENTITY_NEW::send, _newEntity);
    mapFunc["S2C_ENTITY_DEAD"] = std::bind(&S2C_ENTITY_DEAD::send, _deadEntity);
    mapFunc["S2C_ENTITY_HIT"] = std::bind(&S2C_ENTITY_HIT::send, _hitEntity);
    mapFunc["S2C_GAME_END"] = std::bind(&S2C_GAME_END::send, _endGame);

    if (mapFunc.contains(arg1) == true) {
        mapFunc[arg1]();
    } else {
        std::cerr << "Invalid Command" << std::endl;
    }
}

void udp_server::handle_receive(const boost::system::error_code &error, std::size_t /*bytes_transferred*/)
{
    if (!error || error == boost::asio::error::message_size) {
        getData(recv_buffer_);
        boost::shared_ptr<std::string> message(new std::string("hello world\n"));
        socket_.async_send_to(boost::asio::buffer(*message), remote_endpoint_,
            boost::bind(&udp_server::handle_send, this, message, boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
        start_receive();
    }
}

void udp_server::handle_send(boost::shared_ptr<std::string> /*msg*/, const boost::system::error_code & /*error*/,
    std::size_t /*bytes_transferred*/)
{
}

void udp_server::start_receive()
{
    recv_buffer_ = {{}};
    socket_.async_receive_from(boost::asio::buffer(recv_buffer_), remote_endpoint_,
        boost::bind(&udp_server::handle_receive, this, boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}