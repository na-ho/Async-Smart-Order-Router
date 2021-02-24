#include <fmt/format.h>

#include "MarketVenueClient.h"

#include "Gateway.h"

int main()
{
	fmt::print("Market Gateway init...\n");
	MarketGateway::Gateway gateway;
	gateway.init();
	gateway.start();
	fmt::print("Market Gateway stopped...\n");
	return 0;
}
