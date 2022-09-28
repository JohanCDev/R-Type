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

/**
 * @brief main function of the server
 *
 * @return 0 if success or 84 if error
 */
int main(void)
{
    std::string res = create_packet(4, "Player4 died");
    stream2hex(res, res);
    std::cout << res;
    return 0;
}