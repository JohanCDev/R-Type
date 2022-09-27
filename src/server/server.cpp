/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** server
*/

#include "server.hpp"

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