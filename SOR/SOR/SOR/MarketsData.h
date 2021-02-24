#pragma once

#include <cuckoohash_map.hh>

#include "MarketSymbolData.h"

namespace SOR 
{
	// for access from feeder
	class MarketsData
	{
	public:
		static void warmUp() {
			if (!s_instance)
				s_instance = new MarketsData;
		}

		static MarketsData* instance()
		{
			return s_instance;
		}

		MarketSymbolData* getSymbolData(const std::string &symbol);
		//void addSymbolData();

	private:
		static MarketsData* s_instance;

		libcuckoo::cuckoohash_map<std::string, MarketSymbolData*> _symbols;
	};
}