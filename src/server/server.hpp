/**
 * @file server.hpp
 * @author Louis Maestre (louis.maestre@epitech.eu)
 * @brief class of udp server
 * @version 0.1
 * @date 2022-10-05
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <array>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bimap.hpp>
#include <boost/thread.hpp>
#include <string>
#include "../Common/Message/Message.hpp"
#include "../Common/Message/MessageType.hpp"
#include "../Common/locked_queue.hpp"

using boost::asio::ip::udp;

typedef boost::bimap<std::size_t, udp::endpoint> ClientList;
typedef ClientList::value_type Client;
// typedef std::pair<std::string, std::size_t> ClientMessage;
typedef std::pair<Message<GameMessage>, std::size_t> ClientMessage;

class NetworkServer {
  private:
    boost::asio::io_service io_service;
    udp::socket socket;
    udp::endpoint server_endpoint;
    udp::endpoint remote_endpoint;
    std::array<char, 1024> recv_buffer;
    boost::thread service_thread;
    ClientList clients;
    std::size_t nextClientID;

    void start_receive();
    void handle_receive(const boost::system::error_code &error, std::size_t bytes_transferred);
    void handle_send(std::string, const boost::system::error_code &, std::size_t){};
    void run_service();
    std::size_t get_client_id(udp::endpoint endpoint);

    void send(std::string pmessage, udp::endpoint target_endpoint);

    void on_client_disconnected(int32_t id);

    LockedQueue<ClientMessage> incomingMessages;

    NetworkServer(NetworkServer &);

  public:
    NetworkServer(unsigned short local_port);
    ~NetworkServer();

    bool HasMessages();
    ClientMessage PopMessage();

    void SendToClient(std::string message, std::size_t clientID);
    void SendToAll(std::string message);

    std::vector<std::function<void(uint32_t)>> clientDisconnectedHandlers;
};
