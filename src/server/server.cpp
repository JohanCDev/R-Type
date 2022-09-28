/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** server
*/

#include "server.hpp"

void udp_server::start_receive()
{
    socket_.async_receive_from(boost::asio::buffer(recv_buffer_), remote_endpoint_,
        boost::bind(&udp_server::handle_receive, this, boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void udp_server::handle_receive(const boost::system::error_code &error, std::size_t /*bytes_transferred*/)
{
    if (!error || error == boost::asio::error::message_size) {
        // recv_buffer = message cli to serv
        boost::shared_ptr<std::string> message(new std::string(make_daytime_string()));
        // message = answer serv to cli
        socket_.async_send_to(boost::asio::buffer(*message), remote_endpoint_,
            boost::bind(&udp_server::handle_send, this, message, boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
        start_receive();
    }
}

void udp_server::handle_send(boost::shared_ptr<std::string> /*msg*/, 
const boost::system::error_code & /*error*/, std::size_t /*bytes_transferred*/)
{
}

int main()
{
    try {
        boost::asio::io_service io_service;
        udp_server server(io_service);
        io_service.run();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}