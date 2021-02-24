#pragma once

#include <boost/asio.hpp>

#include "Factory_handle_market_type.h"

namespace MarketGateway
{
	class MarketVenueClient
	{
	public:
		MarketVenueClient(boost::asio::io_context& io_context);
		HASHMAP_LAMBDA_MSG_FIX* getFixMsgLambda();

		void connect(const std::string& ip, const std::string& port);
		

	private:
		void do_connect(boost::asio::ip::tcp::resolver::results_type& endpoints);
		void do_read();

		////
		enum { chunksize = 4096 };
		enum { max_fix_read_length = 1 << 20, max_fix_write_length = 1 << 13 };
		char _buffer[max_fix_read_length];
		char _bufferSend[max_fix_write_length];
		unsigned int buffer_read_length;
		/////////
		boost::asio::io_context& _io_context;
		boost::asio::ip::tcp::socket _socket;
		/////////

		HASHMAP_LAMBDA_MSG_FIX _fixMsgLambda;

	};
}