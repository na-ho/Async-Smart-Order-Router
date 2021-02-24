#pragma once

#include "libs/libcuckoo/cuckoohash_map.hh"
#include "Order.h"
#include "User.h"

namespace SOR
{
	class OrderManager 
	{
	public:
		static void warmUp() {
			if (!s_instance)
				s_instance = new OrderManager;
		}

		static OrderManager* instance()
		{
			return s_instance;
		}

		// User std::move to avoid copy
		void addNewOrder(std::string user_id, std::string client_order_id, std::string symbol,
			std::string server_id, int preferred_venue_id, int side, float price, float qty);
	private:
		static OrderManager* s_instance;

		//libcuckoo::cuckoohash_map<unsigned int, Order*> _mpOrders;
		libcuckoo::cuckoohash_map<std::string, User*> _users;
	};
}