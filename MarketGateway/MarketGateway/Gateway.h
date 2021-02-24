#pragma once

#include <cuckoohash_map.hh>

#include "MarketVenueClient.h"
#include "MarketVenueClient_context_pool.h"

namespace MarketGateway
{
	class Gateway {
	public:
		Gateway();

		void init();
		void start();
		void connect();

	private:
		libcuckoo::cuckoohash_map<unsigned int, MarketVenueClient*> _marketVenueClients;
		MarketVenueClient_context_pool* _marketVenueClient_context_pool;
	};
}