#pragma once

#include "../Common/locked_queue.h"

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

#include <array>
#include <memory>

using boost::asio::ip::udp;

class NetworkClient {
  public:
    NetworkClient(std::string host, std::string server_port, unsigned short local_port = 0);
    ~NetworkClient();

    void Send(std::string message);
    inline bool HasMessages();
    inline std::string PopMessage();

  private:
    boost::asio::io_service io_service;
    udp::socket socket;
    udp::endpoint server_endpoint;
    udp::endpoint remote_endpoint;
    std::array<char, 1024> recv_buffer;
    boost::thread service_thread;

    LockedQueue<std::string> incomingMessages;

    void start_receive();
    void handle_receive(const boost::system::error_code &error, std::size_t bytes_transferred);
    void run_service();

    NetworkClient(NetworkClient &);
};