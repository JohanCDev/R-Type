/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** server
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <ctime>
#include <iostream>
#include <string>
#include <boost/shared_ptr.hpp>

using boost::asio::ip::udp;

std::string make_daytime_string()
{
    using namespace std; // For time_t, time and ctime;
    time_t now = time(0);
    return ctime(&now);
}

class udp_server {
  public:
    udp_server(boost::asio::io_service &io_service) : socket_(io_service, udp::endpoint(udp::v4(), 1313))
    {
        start_receive();
    }

  private:
    void start_receive()
    {
        socket_.async_receive_from(boost::asio::buffer(recv_buffer_), remote_endpoint_,
            boost::bind(&udp_server::handle_receive, this, boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
    }

    void handle_receive(const boost::system::error_code &error, std::size_t /*bytes_transferred*/)
    {
        if (!error || error == boost::asio::error::message_size) {
            boost::shared_ptr<std::string> message(new std::string(make_daytime_string()));

            socket_.async_send_to(boost::asio::buffer(*message), remote_endpoint_,
                boost::bind(&udp_server::handle_send, this, message, boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));

            start_receive();
        }
    }

    void handle_send(boost::shared_ptr<std::string> msg, const boost::system::error_code & /*error*/,
        std::size_t /*bytes_transferred*/)
    {
        std::cout << msg.get()->at(0) << std::endl;
    }

    udp::socket socket_;
    udp::endpoint remote_endpoint_;
    boost::array<char, 1> recv_buffer_;
};

#endif /* !SERVER_HPP_ */
