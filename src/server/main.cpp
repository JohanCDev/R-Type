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

#define _WIN32_WINNT 0x0601

#include <iostream>
#include "server.hpp"

#include <chrono>
#include <thread>

#include "../Common/Message/Message.hpp"
#include "../Common/Message/MessageType.hpp"

int main()
{
    NetworkServer server(60000);

    while (1) {
        while (server.HasMessages()) {
            //std::string txt = server.PopMessage().first;
            //std::cout << txt << std::endl;

            Message<GameMessage> gameMsg = server.PopMessage().first;

            std::string tmp(gameMsg.body.begin(), gameMsg.body.end());

            switch (gameMsg.header.id) {
                case (GameMessage::C2S_JOIN): std::cout << "User Joined with message:" << tmp << std::endl; break;
                case (GameMessage::C2S_LEAVE): std::cout << "User Left with message:" << tmp << std::endl; break;
                default: std::cout << "Unkown Message" << std::endl; break;
            }

            if (tmp == "bye") {
                break;
            }
        };
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    }
    return 0;
}
