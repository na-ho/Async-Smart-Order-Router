#pragma once

#include <vector>
#include <set>

#include "MarketEntity.h"

namespace SOR 
{
	typedef std::set<SOR::MarketEntity<float, float>, SOR::MarketEntityCmpLessBegin<float, float>> TYPE_MARKET_VENUE_SELL;
	typedef std::set<SOR::MarketEntity<float, float>, SOR::MarketEntityCmpMoreBegin<float, float>> TYPE_MARKET_VENUE_BUY;

	class MarketVenue 
	{
	public:
		void set(int venue_id);
		int getVenue_id() const;

		TYPE_MARKET_VENUE_SELL* getSellSide();
		TYPE_MARKET_VENUE_BUY* getBuySide();

	private:
		TYPE_MARKET_VENUE_SELL _sell;
		TYPE_MARKET_VENUE_BUY _buy;
		int _venue_id;
	};
}
