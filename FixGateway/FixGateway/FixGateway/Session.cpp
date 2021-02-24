#include <memory>
#include <fmt/format.h>
#include <iostream>
#include <fmt/printf.h>

#include "libs/hffix/hffix.hpp"
#include "Session.h"

#include "util/UtilString.h"
#include "PreHeader.h"
#include "FixGatewayData.h"

using namespace FixGateway;

Session::Session(boost::asio::ip::tcp::socket socket, const HASHMAP_LAMBDA_MSG_FIX *mpFixMsgLambda)
	: _socket(std::move(socket))
	, _fixMsgLambda(mpFixMsgLambda)
	, _seq_send(0)
{
}

void Session::start()
{
	do_read();
}

void Session::do_read()
{
	buffer_read_length = 0;
	auto self(shared_from_this());
	_socket.async_read_some(boost::asio::buffer(_buffer, chunksize),
		[this, self](boost::system::error_code ec, std::size_t length)
		{
			if (!ec)
			{
				buffer_read_length += length;
				//fmt::printf("read some data : %.*s\n", length, _buffer);
				hffix::message_reader reader(_buffer, length);
				
				for (; reader.is_complete(); reader = reader.next_message_reader()) {
					if (reader.is_valid()) {
						auto msgType = reader.message_type()->value().as_string();
						auto handleFunctionIt = _fixMsgLambda->find(msgType);
						if (handleFunctionIt != _fixMsgLambda->end()) {
							handleFunctionIt->second(&reader, this);
						}
					}
				}
				buffer_read_length = reader.buffer_end() - reader.buffer_begin();
				if (buffer_read_length > 0) {
					std::memmove(_buffer, reader.buffer_begin(), buffer_read_length);
				}
			}

			do_read();
		});
}

void Session::do_write(const char *data, std::size_t length)
{
	auto self(shared_from_this());
	boost::asio::async_write(_socket, boost::asio::buffer(data, length),
		[this, self](boost::system::error_code ec, std::size_t length)
		{
			if (ec)
			{
				fmt::print("error_code : {}\n", ec.message());
			}
		});
}

void Session::write_fix_login(const std::string & userID, const char * msgType, const char* data)
{
	auto sizeB = sizeof(_bufferSend);
	hffix::message_writer logon(_bufferSend, _bufferSend + sizeof(_bufferSend));

	logon.push_back_header(FIX_SENDING_VERSION);
	logon.push_back_string(hffix::tag::MsgType, msgType);
	logon.push_back_string(hffix::tag::SenderCompID, GATEWAY_NAME);
	logon.push_back_string(hffix::tag::TargetCompID, userID);
	logon.push_back_int(hffix::tag::MsgSeqNum, _seq_send++);
	//logon.push_back_timestamp(hffix::tag::SendingTime, tsend);
	auto now = boost::posix_time::second_clock::local_time();
	logon.push_back_timestamp(hffix::tag::SendingTime, now.date().year(), now.date().month(), now.date().day(), now.time_of_day().hours()
		, now.time_of_day().minutes(), now.time_of_day().seconds());

	logon.push_back_string(hffix::tag::Text, data);
	logon.push_back_trailer();

	do_write(_bufferSend, logon.message_end() - _bufferSend);

}

User* Session::getUser()
{
	return _user;
}

void Session::setUser(User* user)
{
	_user = user;
}

