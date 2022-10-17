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

#define _WIN32_WINNT 0x0601

#include "server.hpp"
#include <boost/bind.hpp>

// std::string udp_server::deserialize(std::string recv)
// {
//     for (int i = 0; i < recv.size(); i++) {
//         recv[i] = ((unsigned char)recv[i]) >> 1;
//     }
//     return (recv);
// }

// std::string udp_server::serialize(std::string recv)
// {
//     for (int i = 0; i < recv.size(); i++) {
//         recv[i] = ((unsigned char)recv[i]) << 1;
//     }
//     return (recv);
// }

NetworkServer::NetworkServer(unsigned short local_port)
    : socket(io_service, udp::endpoint(udp::v4(), local_port)),
      service_thread(std::bind(&NetworkServer::run_service, this)), nextClientID(0L)
{
}

NetworkServer::~NetworkServer()
{
    io_service.stop();
    service_thread.join();
}

void NetworkServer::start_receive()
{
    socket.async_receive_from(boost::asio::buffer(recv_buffer), remote_endpoint,
        boost::bind(&NetworkServer::handle_receive, this, boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void NetworkServer::handle_receive(const boost::system::error_code &error, std::size_t bytes_transferred)
{
    if (!error) {
        try {
            auto message = ClientMessage(std::string(recv_buffer.data(), recv_buffer.data() + bytes_transferred),
                get_client_id(remote_endpoint));
            if (!message.first.empty())
                incomingMessages.push(message);
        } catch (std::exception ex) {
        } catch (...) {
        }
    } else {
    }

    start_receive();
}

void NetworkServer::send(std::string message, udp::endpoint target_endpoint)
{
    socket.send_to(boost::asio::buffer(message), target_endpoint);
}

void NetworkServer::run_service()
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

std::size_t NetworkServer::get_client_id(udp::endpoint endpoint)
{
    auto cit = clients.right.find(endpoint);
    if (cit != clients.right.end())
        return (*cit).second;

    nextClientID++;
    clients.insert(Client(nextClientID, endpoint));
    return nextClientID;
}

void NetworkServer::SendToClient(std::string message, std::size_t clientID)
{
    try {
        send(message, clients.left.at(clientID));
    } catch (std::out_of_range) {
    }
}

void NetworkServer::SendToAll(std::string message)
{
    for (auto client : clients)
        send(message, client.right);
}

void NetworkServer::on_client_disconnected(int32_t id)
{
    for (auto &handler : clientDisconnectedHandlers)
        if (handler)
            handler(id);
}

ClientMessage NetworkServer::PopMessage()
{
    return incomingMessages.pop();
}

bool NetworkServer::HasMessages()
{
    return !incomingMessages.empty();
}
