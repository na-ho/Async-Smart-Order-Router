#pragma once

#include <boost/asio.hpp>

class Server
{
public:
    Server(boost::asio::io_context& io_context, short port);

private:
    void do_accept();

    void initFixLogon();
   
    std::map<std::string, std::any> mpFixMsgLambda;

    boost::asio::ip::tcp::acceptor acceptor_;
};
