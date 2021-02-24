#pragma once

#include <boost/asio.hpp>
#include <string>

#include "UserManager.h"
#include "Session.h"
#include "libs/hffix/hffix.hpp"

#define HASHMAP_LAMBDA_MSG_FIX std::unordered_map<std::string, std::function<void(hffix::message_reader*, Session*)>> 

namespace FixGateway
{
    class Session : public std::enable_shared_from_this<Session>
    {
    public:

        Session(boost::asio::ip::tcp::socket socket, const HASHMAP_LAMBDA_MSG_FIX* mpFixMsgLambda);

        void start();

        void write_fix_login(const std::string& userID, const char* msgType, const char* data);
        User* getUser();
        void setUser(User* user);

    private:
        void do_read();
        void do_write(const char* data, std::size_t length);


        boost::asio::ip::tcp::socket _socket;
        enum { chunksize = 4096};
        enum { max_fix_read_length = 1 << 20, max_fix_write_length = 1 << 13 };
        char _buffer[max_fix_read_length];
        char _bufferSend[max_fix_write_length];
        unsigned int buffer_read_length;
        unsigned int _seq_send;
        User* _user;

        const HASHMAP_LAMBDA_MSG_FIX* _fixMsgLambda;

    };
}