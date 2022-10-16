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
#include "server.hpp"

#include <chrono>
#include <thread>

#include "../Common/Message/Message.h"

int main()
{
    NetworkServer server(60000);

    while (1) {
        while (server.HasMessages()) {
            std::string txt = server.PopMessage().first;
            std::cout << txt << std::endl;

            if (txt == "bye") {
                break;
            }
        };
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    }
    return 0;
}
