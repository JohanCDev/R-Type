/**
 * @file main.cpp
 * @author Johan Chrillesen (johan.chrillesen@epitech.eu)
 * @brief Main file of the server
 * @version 0.1
 * @date 2022-09-20
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>
#include "utils.hpp"
#include "Package.hpp"

/**
 * @brief main function of the server
 *
 * @return 0 if success or 84 if error
 */
int main(void)
{
    try {
        boost::asio::io_service io_service;
        udp_server server(io_service);
        io_service.run();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    // stream2hex(res, res);
    // std::cout << res;
    return 0;
}