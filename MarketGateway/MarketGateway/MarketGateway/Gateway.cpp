#include "Gateway.h"
#include "Factory_handle_market_type_a.h"

MarketGateway::Gateway::Gateway()
{
}

void MarketGateway::Gateway::init()
{
	const unsigned int marketVenue_size = 1;

	_marketVenueClient_context_pool = new MarketVenueClient_context_pool(marketVenue_size);

	// for test, in production will read from a config file
	auto io_contexts = _marketVenueClient_context_pool->get_io_contexts();
//	for(auto io_context : (*io_contexts)) {
	for (unsigned int iVenue = 0; iVenue < marketVenue_size; ++iVenue) {
		auto market_venue = new MarketVenueClient(*(io_contexts->at(iVenue)));
		auto fixMsgLamda = market_venue->getFixMsgLambda();
		Factory_handle_market_type_a::setLambda(fixMsgLamda, market_venue);
		_marketVenueClients.insert(iVenue, market_venue);
	}
}

void MarketGateway::Gateway::start()
{
	connect();
	_marketVenueClient_context_pool->run();
}

void MarketGateway::Gateway::connect()
{
	// for test, in production will read from a config file
	MarketVenueClient* client = NULL;
	if (_marketVenueClients.find(0, client)) {
		client->connect("127.0.0.1", "15000");
	}
	
}
