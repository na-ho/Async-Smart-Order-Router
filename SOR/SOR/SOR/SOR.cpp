#include <fmt/format.h>

#include "MsgBus.h"
#include "MarketsData.h"
#include "OrderManager.h"

using namespace std;

void warmUp() {
	SOR::MarketsData::warmUp();
	SOR::OrderManager::warmUp();
}

void simTest() {
}

int main()
{
	warmUp();
	simTest();

	SOR::MsgBus msgBus;
	fmt::print("SOR init...\n");
	msgBus.init();
	fmt::print("SOR Waiting ...\n");
	msgBus.sleep_forever();

	return 0;
}
