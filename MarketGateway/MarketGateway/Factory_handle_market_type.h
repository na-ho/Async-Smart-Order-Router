#pragma once

#include <unordered_map>

#include "libs/hffix/hffix.hpp"

#define HASHMAP_LAMBDA_MSG_FIX std::unordered_map<std::string, std::function<void(hffix::message_reader*, MarketGateway::MarketVenueClient*)>> 

namespace MarketGateway
{
	class MarketVenueClient;
	// factory class
	class Handle_market_type {
	public:
		virtual void init(HASHMAP_LAMBDA_MSG_FIX *pLambda) = 0;
	};
}