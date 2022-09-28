/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** thread
*/

#include "thread.hpp"

// Multi Threading program example.

void printer::print1()
{
    if (count_ < 10) {
        std::cout << "Timer 1: " << count_ << std::endl;
        ++count_;

        timer1_.expires_at(timer1_.expiry() + asio::chrono::seconds(1));
        timer1_.async_wait(asio::bind_executor(strand_, boost::bind(&printer::print1, this)));
    }
}

void printer::print2()
{
    if (count_ < 10) {
        std::cout << "Timer 2: " << count_ << std::endl;
        ++count_;

        timer2_.expires_at(timer2_.expiry() + asio::chrono::seconds(1));

        timer2_.async_wait(asio::bind_executor(strand_, boost::bind(&printer::print2, this)));
    }
}