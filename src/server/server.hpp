/**
 * @file server.hpp
 * @author Adam Djebar (adam.djebar@epitech.eu)
 * @brief class of udp server
 * @version 0.1
 * @date 2022-10-05
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

/**
 * @brief Define boost placeholders
 */
#define BOOST_BIND_GLOBAL_PLACEHOLDERS

#include <array>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bimap.hpp>
#include <boost/thread.hpp>
#include <string>
#include "../Common/Message/Message.hpp"
#include "../Common/Message/MessageType.hpp"
#include "../Common/locked_queue.hpp"

/**
 * @brief Define the maximum of clients able to connect
 *
 */
#define MAX_CLIENTS 4

using boost::asio::ip::udp;

/**
 * @brief List of all the clients
 *
 */
typedef boost::bimap<std::size_t, udp::endpoint> ClientList;
/**
 * @brief Define a value value_type for the client
 *
 */
typedef ClientList::value_type Client;
// typedef std::pair<std::string, std::size_t> ClientMessage;
/**
 * @brief Define a pair of messages and size
 *
 */
typedef std::pair<Message<GameMessage>, std::size_t> ClientMessage;

/**
 * @brief Network server class containing all infos of server network
 *
 */
class NetworkServer {
  private:
    boost::asio::io_service io_service;
    udp::socket socket;
    udp::endpoint server_endpoint;
    udp::endpoint remote_endpoint;
    std::array<char, 1024> recv_buffer;
    boost::thread service_thread;
    std::size_t nextClientID;

    void start_receive();
    void handle_receive(const boost::system::error_code &error, std::size_t bytes_transferred);
    void handle_send(std::string, const boost::system::error_code &, std::size_t){};
    void run_service();
    std::size_t get_client_id(udp::endpoint endpoint);

    void send(std::string pmessage, udp::endpoint target_endpoint);
    void send(const Message<GameMessage> &message, udp::endpoint target_endpoint);

    void on_client_disconnected(std::size_t id);

    LockedQueue<ClientMessage> incomingMessages;

    NetworkServer(NetworkServer &);

  public:
    /**
     * @brief Construct a new Network Server object
     *
     * @param local_port port to connect the client
     */
    NetworkServer(unsigned short local_port);

    /**
     * @brief Destroy the Network Server object
     *
     */
    ~NetworkServer();

    /**
     * @brief Check if the server has messages to receive
     *
     * @return True if there is. False if there isn't any
     */
    bool HasMessages();

    /**
     * @brief Pop incoming message
     *
     * @return Message as a ClientMessage class
     */
    ClientMessage PopMessage();

    /**
     * @brief Send a message to a specific client
     *
     * @param message message to send
     * @param clientID ID of the client to notify
     */
    void SendToClient(std::string message, std::size_t clientID);

    /**
     * @brief Send a message to all clients connected
     *
     * @param message message to send
     */
    void SendToAll(std::string message);

    /**
     * @brief Send a message to all clients except one
     *
     * @param message message to send
     * @param clientID ID of the client to ignore
     */
    void SendToAllExcept(std::string message, std::size_t clientID);

    /**
     * @brief Send a message to a specific client
     *
     * @param message message to send
     * @param clientID ID of the client to notify
     */
    void SendToClient(const Message<GameMessage> &message, std::size_t clientID);

    /**
     * @brief Send a message to all clients connected
     *
     * @param message message to send
     */
    void SendToAll(const Message<GameMessage> &message);

    /**
     * @brief Send a message to all clients except one
     *
     * @param message message to send
     * @param clientID ID of the client to ignore
     */
    void SendToAllExcept(const Message<GameMessage> &message, std::size_t clientID);

    /**
     * @brief Vector containing all the function needed to handle the disconnected clients
     *
     */
    std::vector<std::function<void(std::size_t)>> clientDisconnectedHandlers;

    /**
     * @brief List of the clients
     *
     */
    ClientList clients;
};
