#pragma once

#include <boost/asio.hpp>

#include "libs/hffix/hffix.hpp"
#include "Session.h"

class Server
{
public:
    Server(boost::asio::io_context& io_context, short port);

private:
    void do_accept();

    void initFixLogon();
   
    MAP_LAMBDA_MSG_FIX _mpFixMsgLambda;

    boost::asio::ip::tcp::acceptor _acceptor;
};
