/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** server
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_

#include "utils.hpp"
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <ctime>
#include <iostream>
#include <string>
#include <boost/shared_ptr.hpp>

using boost::asio::ip::udp;

std::string create_packet(size_t type, std::string content)
{
    char c_type[1];
    char length[1];
    std::string result;

    push_back_byte(c_type, type);
    push_back_byte(length, content.size());
    result.append(c_type);
    result.append(length);
    // result.pop_back();
    result.append(content);
    return result;
}

std::string make_daytime_string()
{
    std::string tmp = "hello world";
    return (tmp);
}

class udp_server {
  public:
    udp_server(boost::asio::io_service &io_service) : socket_(io_service, udp::endpoint(udp::v4(), 1313))
    {
        start_receive();
    }

  private:
    void start_receive();

    void handle_receive(const boost::system::error_code &error, std::size_t /*bytes_transferred*/);

    void handle_send(boost::shared_ptr<std::string> /*msg*/, 
    const boost::system::error_code & /*error*/, std::size_t /*bytes_transferred*/);

    udp::socket socket_;
    udp::endpoint remote_endpoint_;
    boost::array<char, 64> recv_buffer_;
};

#endif /* !SERVER_HPP_ */
