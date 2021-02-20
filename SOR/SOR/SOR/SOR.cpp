#include <fmt/format.h>

#include "SOR.h"
#include "MsgBus.h"

using namespace std;

int main()
{
	SOR::MsgBus msgBus;
	fmt::print("SOR init...\n");
	msgBus.init();
	fmt::print("SOR Waiting ...\n");
	msgBus.sleep_forever();

	return 0;
}
