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

class NetworkClient {
  public:
    NetworkClient(std::string host, std::string server_port, unsigned short local_port = 0);
    ~NetworkClient();

    void send(const std::string &message);
    void send(const Message<GameMessage> &message);
    bool HasMessages();
    Message<GameMessage> PopMessage();
    void processMessage(Message<GameMessage> &msg, World &world, sf::RenderWindow &window, SceneScreen &actual_screen);

    void set_launch_game(bool launch);
    bool get_launch_game() const;

    void set_players_ready(bool ready);
    bool get_players_ready() const;

    void set_nb_players(int nb_players);
    int get_nb_players() const;

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

    LockedQueue<Message<GameMessage>> incomingMessages;

    void start_receive();
    void handle_receive(const std::error_code &error, std::size_t bytes_transferred);
    void run_service();

    NetworkClient(NetworkClient &);
};
