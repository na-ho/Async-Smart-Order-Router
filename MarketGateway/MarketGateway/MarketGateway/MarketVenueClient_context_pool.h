#pragma once

#include <thread>
#include <list>

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>

namespace MarketGateway
{
	class MarketVenueClient_context_pool
	{
	public:
		typedef std::vector<boost::asio::io_context*> type_io_contexts;

		explicit MarketVenueClient_context_pool(std::size_t pool_size);

		void run();
		void stop();

		type_io_contexts* get_io_contexts();

	private:
		typedef boost::shared_ptr<boost::asio::io_context> io_context_ptr;

		std::vector<boost::asio::io_context*> _io_contexts;
		std::vector<std::thread> _threads;
	};
}