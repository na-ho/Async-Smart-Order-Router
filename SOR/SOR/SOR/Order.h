#pragma once

#include <string>

#include "MarketVenue.h"

namespace SOR
{
	class User;
	class MarketSymbolData;

	enum Side {Buy=1, Sell=2};

	// if use template to select side, it will cost at lookup from MarketGateway but not cost when calculate

//	template<Side T>
	class Order
	{
	public:
		enum STATUS
		{
			READY = 0,	// ready for action , e.g. order is already set in place
			WAITING		// waiting markets to execute the order
		};
		Order();

		void set(User *user, std::string client_order_id, std::string symbol, int preferred_venue_id, int side, float price, float qty);
		void caculate_send_route();
		int getStatus() const;
		std::string getClient_order_id() const;
		void sendOrder(int venue_id, float price, float qty);
	private:
		User* _user;
		/////////////////

		std::string _client_order_id;
		std::string _symbol;
		int _preferred_venue_id;
		int _side;
		float _price;
		float _qty;
		float _qtyOrg;

		/////////////////
		int _status;
		MarketSymbolData* _marketSymbolData;

		TYPE_MARKET_VENUE_SELL _tempSell;
	};
}