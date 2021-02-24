#include <fmt/format.h>

#include "Order.h"
#include "MarketsData.h"
#include "MarketSymbolData.h"
#include "Utils.h"

SOR::Order::Order()
	:_status(READY)
{
}

void SOR::Order::set(User* user, std::string client_order_id, std::string symbol, int preferred_venue_id, int side, float price, float qty)
{
	_user = user;
	_client_order_id = std::move(client_order_id);
	_symbol = std::move(symbol);
	_preferred_venue_id = preferred_venue_id;
	_side = side;
	_price = price;
	_qty = _qtyOrg = qty;

	// TODO: have to have protection mechanism in case of not found
	_marketSymbolData = MarketsData::instance()->getSymbolData(symbol);
	_marketSymbolData->registerOrder(this);

}

// TODO: better algorithm to split the multiple orders
void SOR::Order::caculate_send_route()
{
	auto marketVenues = _marketSymbolData->getMarketVenues();
	if (_qty > 0) {
		if (_side == Side::Buy) {
			bool stop = false;

			_tempSell.clear();
			// lock due to async ,while reading all venue
			auto marketVenusIt = marketVenues->lock_table();
			for (const auto& venueIt : marketVenusIt) {
				auto venue = venueIt.second;
				auto sellSide = venue->getSellSide(); // because now, the order is buying

				/*std::merge(_tempSell.begin(), _tempSell.end(),
					sellSide->begin(), sellSide->end(),
					std::inserter(s, s.begin()));*/

				_tempSell.insert(sellSide->begin(), sellSide->end());
			}

			for (const auto& mktEnt : _tempSell) { // alreay sorted
				if (!(mktEnt._price > _price)) {
					// send order to market gateway
					if (_qty > mktEnt._qty)
					{
						_qty -= mktEnt._qty;
						sendOrder(mktEnt._marketVenue->getVenue_id(), mktEnt._price, mktEnt._qty);
					}
					else {
						sendOrder(mktEnt._marketVenue->getVenue_id(), mktEnt._price, _qty);
						_qty = 0;
						stop = true;
						break;
					}

				}
				if (stop) {
					break;
				}
			}
		}
		else {

		}
	}

}

int SOR::Order::getStatus() const
{
	return _status;
}

std::string SOR::Order::getClient_order_id() const
{
	return _client_order_id;
}

void SOR::Order::sendOrder(int venue_id, float price, float qty)
{
	// TODO
}
