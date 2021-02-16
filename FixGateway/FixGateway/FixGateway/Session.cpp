#include <memory>
#include <fmt/format.h>
#include <iostream>
#include <fmt/printf.h>

#include "libs/hffix/hffix.hpp"
#include "Session.h"

#include "util/UtilString.h"
#include "PreHeader.h"
#include "FixGatewayData.h"

Session::Session(boost::asio::ip::tcp::socket socket)
	: _socket(std::move(socket))
	, _seq_send(0)
{
	_userMgr = FixGatewayData::instance()->getUserMgr();
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
				if (UtilString::fast_compare(reader.message_type()->value().begin(), "A", 1) == 0) {
					// login

					fmt::print("login\n");
					hffix::message_reader::const_iterator i = reader.begin();
					if (reader.find_with_hint(hffix::tag::SenderCompID, i)) {
						auto userId = i++->value().as_string();
						fmt::print("userId : {}\n", userId);
						if (reader.find_with_hint(hffix::tag::RawData, i)) {
							auto password = i++->value().as_string();
							if (_userMgr->checkAuthorization(userId, password)) {
								// insert into map
							}
							else {
								write_fix_login(userId, "Password invalid");
							}
						}
						else {
							// cannot find password
							write_fix_login(userId, "Cannot find password");
						}
					}

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

void Session::write_fix_login(const std::string & userID, const char* data)
{
	auto sizeB = sizeof(_bufferSend);
	hffix::message_writer logon(_bufferSend, _bufferSend + sizeof(_bufferSend));

//	boost::posix_time::ptime tsend(boost::gregorian::date(2017, 8, 9), boost::posix_time::time_duration::time_duration(12, 34, 56));
	logon.push_back_header(FIX_SENDING_VERSION);
	logon.push_back_string(hffix::tag::MsgType, "5");
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
