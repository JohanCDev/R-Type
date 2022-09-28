/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** printer
*/

#ifndef PRINTER_HPP_
#define PRINTER_HPP_

#include <asio.hpp>
#include <boost/bind/bind.hpp>
// #include <boost/thread/thread.hpp>
#include <iostream>

class printer {
  public:
    printer(asio::io_context &io)
        : strand_(asio::make_strand(io)), timer1_(io, asio::chrono::seconds(1)), timer2_(io, asio::chrono::seconds(1)),
          count_(0)
    {
        timer1_.async_wait(asio::bind_executor(strand_, boost::bind(&printer::print1, this)));

        timer2_.async_wait(asio::bind_executor(strand_, boost::bind(&printer::print2, this)));
    }

    void print1();
    void print2();

    ~printer()
    {
        std::cout << "Final count is " << count_ << std::endl;
    }

  private:
    asio::strand<asio::io_context::executor_type> strand_;
    asio::steady_timer timer1_;
    asio::steady_timer timer2_;
    int count_;
};

#endif /* !PRINTER_HPP_ */
