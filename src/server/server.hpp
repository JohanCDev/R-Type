/**
 * @file server.hpp
 * @author your name (you@domain.com)
 * @brief class of udp server
 * @version 0.1
 * @date 2022-10-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <ctime>
#include <iostream>
#include <string>
#include "utils.hpp"
#include <boost/shared_ptr.hpp>

using boost::asio::ip::udp;

class udp_server {
  private:
    void start_receive();

    void handle_receive(const boost::system::error_code &error, std::size_t /*bytes_transferred*/);

    void handle_send(boost::shared_ptr<std::string> /*msg*/, const boost::system::error_code & /*error*/,
        std::size_t /*bytes_transferred*/);


    udp::socket socket_;
    udp::endpoint remote_endpoint_;
    boost::array<char, 64> recv_buffer_;

  public:
    void getData(boost::array<char, 64>);
    udp_server(boost::asio::io_service &io_service) : socket_(io_service, udp::endpoint(udp::v4(), 1313))
    {
        start_receive();
    }
};

#endif /* !SERVER_HPP_ */
