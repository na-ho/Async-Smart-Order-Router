#include "MarketSymbolData.h"

void SOR::MarketSymbolData::registerOrder(Order* order)
{
	_orders.insert(std::move(order->getClient_order_id()), order);
}

TYPE_MARKET_SYMBOL_DATA* SOR::MarketSymbolData::getMarketVenues()
{
	return &_market_symbol_data;
}
