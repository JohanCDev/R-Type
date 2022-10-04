/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** server
*/

#include "server.hpp"
#include "Package.hpp"

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

void udp_server::getData(boost::array<char, 64> recv_buffer_)
{
    std::istringstream tmp(recv_buffer_.data());
    std::string arg1;
    std::string size;
    std::string desc = recv_buffer_.data();

    // std::string tmp;
    S2C_OK _ok;
    S2C_ERROR _error;
    S2C_MOVEMENT _mvt;
    S2C_ENTITY_NEW _newEntity;
    S2C_ENTITY_DEAD _deadEntity;
    S2C_ENTITY_HIT _hitEntity;
    S2C_GAME_END _endGame;
    std::map<std::string, std::function<void()>> mapFunc;


    tmp >> arg1 >> size;
    mapFunc["S2C_OK"] = std::bind(&S2C_OK::send, _ok);
    mapFunc["S2C_ERROR"] = std::bind(&S2C_ERROR::send, _error);
    mapFunc["S2C_MOVEMENT"] = std::bind(&S2C_MOVEMENT::send, _mvt);
    mapFunc["S2C_ENTITY_NEW"] = std::bind(&S2C_ENTITY_NEW::send, _newEntity);
    mapFunc["S2C_ENTITY_DEAD"] = std::bind(&S2C_ENTITY_DEAD::send, _deadEntity);
    mapFunc["S2C_ENTITY_HIT"] = std::bind(&S2C_ENTITY_HIT::send, _hitEntity);
    mapFunc["S2C_GAME_END"] = std::bind(&S2C_GAME_END::send, _endGame);

    auto tmmp = mapFunc[arg1];

    tmmp();
    // mapFunc.emplace(std::make_pair("hello", &S2C_OK::send));

    // mapFunc["hello"];

    // tempo["tempo"] = func;
    // switch (arg1)
    // {
    // case "hello":
    //     /* code */
    //     break;
    
    // default:
    //     break;
    // }
    // std::cout << desc.substr(arg1.size() + size.size() + 2, std::stoi(size)) << std::endl;
    // std::cout << arg1 << std::endl;
}

void udp_server::handle_receive(const boost::system::error_code &error, std::size_t /*bytes_transferred*/)
{
    if (!error || error == boost::asio::error::message_size) {
        getData(recv_buffer_);
        boost::shared_ptr<std::string> message(new std::string(make_daytime_string()));
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

void udp_server::start_receive()
{
    socket_.async_receive_from(boost::asio::buffer(recv_buffer_), remote_endpoint_,
        boost::bind(&udp_server::handle_receive, this, boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

// int main()
// {
//     try {
//         boost::asio::io_service io_service;
//         udp_server server(io_service);
//         io_service.run();
//     } catch (std::exception &e) {
//         std::cerr << e.what() << std::endl;
//     }
//     return 0;
// }