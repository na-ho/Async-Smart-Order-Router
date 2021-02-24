#pragma once

#include <unordered_map>
#include <set>

#include "MarketVenue.h"
#include "Order.h"
#include "cuckoohash_map.hh"

#define TYPE_MARKET_SYMBOL_DATA libcuckoo::cuckoohash_map<int, SOR::MarketVenue*>

namespace SOR
{
	class MarketSymbolData
	{
	public:

		void registerOrder(Order *order);
		TYPE_MARKET_SYMBOL_DATA* getMarketVenues();


	private:
		// market venues for this symbol 
		TYPE_MARKET_SYMBOL_DATA _market_symbol_data;

		// orders which are associate with this symbol, need to be recalculated
		// which frequently add and remove but not access from this side
		libcuckoo::cuckoohash_map<std::string, Order*> _orders;
	};
}