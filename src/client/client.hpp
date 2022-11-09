/**
 * @file client.hpp
 * @author Adam Djebar (adam.djebar@epitech.eu)
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
#include "../Common/Message/Message.hpp"
#include "../Common/Message/MessageType.hpp"
#include "../ECS/World.hpp"
#include "../Common/locked_queue.hpp"

using boost::asio::ip::udp;

class NetworkClient {
  public:
    /**
     * @brief Construct a new Network Client object
     *
     * @param host host to connect to
     * @param server_port port of the server
     * @param local_port local port to connect
     */
    NetworkClient(std::string host, std::string server_port, unsigned short local_port = 0);
    /**
     * @brief Destroy the Network Client object
     *
     */
    ~NetworkClient();

    /**
     * @brief Send a message to the server
     *
     * @param message message to send
     */
    void send(const std::string &message);

    /**
     * @brief Send a message to the server
     *
     * @param message message to send
     */
    void send(const Message<GameMessage> &message);

    /**
     * @brief Check if client has incoming messages of the server
     *
     * @return True if there is. False if there isn't any.
     */
    bool HasMessages();

    /**
     * @brief Pop incoming message from the server
     *
     * @return Message<GameMessage> object containing the message
     */
    Message<GameMessage> PopMessage();

    /**
     * @brief Process a message
     *
     * @param msg message to process
     * @param world Game Class that will be modified by the message
     */
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
