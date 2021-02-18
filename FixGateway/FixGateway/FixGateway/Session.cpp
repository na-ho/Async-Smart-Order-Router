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
	auto self(shared_from_this());
	_socket.async_read_some(boost::asio::buffer(_buffer, max_length),
		[this, self](boost::system::error_code ec, std::size_t length)
		{
			if (!ec)
			{
				fmt::printf("read some data : %.*s\n", length, _buffer);
				//	std::cout << "read some data : " << data_ << std::endl;
				//	std::cout << "read some length : " << length << std::endl;
				hffix::message_reader reader(_buffer, length);
				//	fmt::print("message_type : {}\n", reader.message_type()->value());
				//	fmt::print("message_type 1 : {}\n", reader.message_type()->value().begin());
				//	auto ptr = reader.message_type()->value();
					//if(UtilString::fast_compare())
					//if (reader.message_type()->value().as_char() == 'A') {
					/*fmt::print("test : {}\n", UtilString::fast_compare("ASD", "ASD", 3));
					fmt::print("test : {}\n", UtilString::fast_compare("ASD", "AS", 3));
					fmt::print("test : {}\n", UtilString::fast_compare("ASD", "ASE", 3));
					fmt::print("test : {}\n", UtilString::fast_compare("AS", "ASE", 2));*/
				//if (UtilString::fast_compare(reader.message_type()->value().begin(), "A", 1) == 0) {
					// login
				//}
				auto msgType = reader.message_type()->value().as_string();
				//(*_mpFixMsgLambda)[msgType](&reader, this);
			//	auto testFunction = (*_mpFixMsgLambda)[msgType];
				//auto handleFunction = _mpFixMsgLambda->at(msgType);
				auto handleFunctionIt = _fixMsgLambda->find(msgType);
				if (handleFunctionIt != _fixMsgLambda->end()) {
					handleFunctionIt->second(&reader, this);
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

//	boost::posix_time::ptime tsend(boost::gregorian::date(2017, 8, 9), boost::posix_time::time_duration::time_duration(12, 34, 56));
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

