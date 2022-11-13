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
#include "scene/Scene.hpp"
#include "../Common/locked_queue.hpp"

using boost::asio::ip::udp;

class World;

enum class SceneScreen : uint32_t;

/**
 * @brief Network client class
 *
 * Containing information on the network used in client
 */
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

    /**
     * @brief Process a message
     *
     * @param msg message to process
     * @param world Game Class that will be modified by the message
     * @param window Window to modify
     * @param current_screen Current screen of the game
     */
    void processMessage(Message<GameMessage> &msg, World &world, sf::RenderWindow &window, SceneScreen &current_screen);

    /**
     * @brief Set the launch value
     *
     * @param launch new launch value
     */
    void set_launch_game(bool launch);
    /**
     * @brief Get the launch value
     *
     * @return the value
     */
    bool get_launch_game() const;

    /**
     * @brief Set the players ready value
     *
     * @param ready new launch value
     */
    void set_players_ready(bool ready);

    /**
     * @brief Get the players_ready value
     *
     * @return the value
     */
    bool get_players_ready() const;

    /**
     * @brief Set the nb players
     *
     * @param nb_players nb_players value
     */
    void set_nb_players(int nb_players);

    /**
     * @brief Get the nb players
     *
     * @return nb_players
     */
    int get_nb_players() const;

    /**
     * @brief Set the nb players
     *
     * @param volume volume value
     */
    void setSoundVolume(float volume);

    /**
     * @brief Get the nb players
     *
     * @return nb_players
     */
    float getSoundVolume() const;

  private:
    boost::asio::io_service io_service;
    udp::socket socket;
    udp::endpoint server_endpoint;
    udp::endpoint remote_endpoint;
    std::array<char, 1024> recv_buffer;
    boost::thread service_thread;
    bool _players_ready;
    bool _launch_game;
    int _nb_players;
    float _sound_volume;

    LockedQueue<Message<GameMessage>> incomingMessages;

    void start_receive();
    void handle_receive(const std::error_code &error, std::size_t bytes_transferred);
    void run_service();

    NetworkClient(NetworkClient &);
};
