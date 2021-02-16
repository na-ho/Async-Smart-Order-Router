#pragma once

#include <boost/asio.hpp>
#include <string>

#include "UserManager.h"
#include "Session.h"
#include "libs/hffix/hffix.hpp"

#define MAP_LAMBDA_MSG_FIX std::map<std::string, std::function<void(hffix::message_reader*, Session*)>> 

class Session
    : public std::enable_shared_from_this<Session>
{
 
public:
    
    Session(boost::asio::ip::tcp::socket socket, const MAP_LAMBDA_MSG_FIX *mpFixMsgLambda);
   
    void start();

    void write_fix_login(const std::string& userID, const char* data);
private:
    void do_read();
    void do_write(const char* data, std::size_t length);

   
    boost::asio::ip::tcp::socket _socket;
    enum { max_length = 1024 };
    char _buffer[max_length];
    char _bufferSend[max_length];
   // std::string _userID;
    unsigned int _seq_send;
    UserManager* _userMgr;

    const MAP_LAMBDA_MSG_FIX *_mpFixMsgLambda;

};