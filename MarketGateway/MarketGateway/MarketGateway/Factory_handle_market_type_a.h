#pragma once
#include <fmt/format.h>
#include "Factory_handle_market_type.h"

namespace MarketGateway
{
	// type a because, each connection of Fix protocol is not the same. Depend on both side how to implement protocol
	// in this case will name temporary as "a", if more than this type just name as want
	// can use config file outside to config logic but will effect the performance 
	class Factory_handle_market_type_a
	{
	public:
		static void setLambda(HASHMAP_LAMBDA_MSG_FIX* pLambda, MarketVenueClient *venueClient) {
			pLambda->emplace("A", [venueClient](hffix::message_reader* reader, MarketVenueClient* client) {
			//	fmt::print("Connect sucessful\n");
				hffix::message_reader::const_iterator i = reader->begin();
				if (reader->find_with_hint(hffix::tag::SenderCompID, i)) {
					auto userId = i++->value().as_string();
				}
				});
		}
	};
}