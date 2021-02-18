#pragma once

#include <boost/asio.hpp>

#include "libs/hffix/hffix.hpp"
#include "Session.h"
#include "UserManager.h"
#include "MsgBus.h"

namespace FixGateway
{

    class Server
    {
    public:
        Server(boost::asio::io_context& io_context, short port);
        ~Server();

    private:
        void do_accept();

        void initFixLogon();
        void initFixOrder();

        void initMsgBus();

        HASHMAP_LAMBDA_MSG_FIX _fixMsgLambda;
        boost::asio::ip::tcp::acceptor _acceptor;
        UserManager* _userMgr;
        MsgBus* _msgBus;
    };

}