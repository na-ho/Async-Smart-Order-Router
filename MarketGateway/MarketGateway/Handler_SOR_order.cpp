#include "Handler_SOR_order.h"

#include "schemas/order_sor_mg_generated.h"

void MarketGateway::Handler_SOR_order::destroy()
{
	natsSubscription_Destroy(sub_fixg_sor_order);
}

void MarketGateway::Handler_SOR_order::subscribe(natsConnection* conn)
{
	natsConnection_Subscribe(&sub_fixg_sor_order, conn, MSGBUS_SOR_MG_ORDER, Handler_SOR_order::onMgs_sor_mg_order, NULL);
	natsSubscription_SetPendingLimits(sub_fixg_sor_order, -1, -1);
}

void MarketGateway::Handler_SOR_order::onMgs_sor_mg_order(MSGBUS_NATS_PARAMETER)
{
	auto data = natsMsg_GetData(msg);

	// read Flatbuffers msg, and send to the specific Market Venue
}
