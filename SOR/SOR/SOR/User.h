#pragma once

#include <string>
#include "cuckoohash_map.hh"

#include "Order.h"

namespace SOR
{
	class User
	{
	public:
		void set(std::string user_id, std::string server_id);
		void checkSet_server_id(std::string server_id);
		void addOrder(std::string client_order_id, std::string symbol, int preferred_venue_id, int side, float price, float qty);
	private:
		std::string _user_id;
		std::string _server_id;

		libcuckoo::cuckoohash_map<std::string, Order*> _orders;
	};
}