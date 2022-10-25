/**
 * @file client.hpp
 * @author  Tanguy Bellicha (tanguy.bellicha@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-10-16
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <array>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <memory>
#include "../ECS/World.hpp"
#include "../Common/Message/Message.hpp"
#include "../Common/Message/MessageType.hpp"
#include "../Common/locked_queue.hpp"

using boost::asio::ip::udp;

class NetworkClient {
  public:
    NetworkClient(std::string host, std::string server_port, unsigned short local_port = 0);
    ~NetworkClient();

    void Send(const std::string &message);
    void SendMessage(const Message<GameMessage> &message);
    bool HasMessages();
    Message<GameMessage> PopMessage();
    void processMessage(Message<GameMessage> &msg, World &world);

  private:
    boost::asio::io_service io_service;
    udp::socket socket;
    udp::endpoint server_endpoint;
    udp::endpoint remote_endpoint;
    std::array<char, 1024> recv_buffer;
    boost::thread service_thread;

    LockedQueue<Message<GameMessage>> incomingMessages;

    void start_receive();
    void handle_receive(const std::error_code &error, std::size_t bytes_transferred);
    void run_service();

    NetworkClient(NetworkClient &);
};
