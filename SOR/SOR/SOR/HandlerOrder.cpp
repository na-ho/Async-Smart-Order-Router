#include <fmt/format.h>

#include "schemas/order_fixg_sor_generated.h"
#include "HandlerOrder.h"
#include "OrderManager.h"

void SOR::HandlerOrder::destroy()
{
	natsSubscription_Destroy(sub_fixg_sor_order);
}

void SOR::HandlerOrder::subscribe(natsConnection* conn)
{
	// distributed workload among SOR services
	natsConnection_QueueSubscribe(&sub_fixg_sor_order, conn, MSGBUS_FIXG_SOR_ORDER, MSGBUS_SOR_QUEUE_GROUP, HandlerOrder::onMgs_fixg_sor_order, NULL);
	natsSubscription_SetPendingLimits(sub_fixg_sor_order, -1, -1);

}

void SOR::HandlerOrder::onMgs_fixg_sor_order(MSGBUS_NATS_PARAMETER)
{
	auto data = natsMsg_GetData(msg);

	// zero copy , aware after destroy
	auto order_data = MsgSerialization::GetOrder_FIXG_SOR(data);

	
	std::string user_id(order_data->user_id()->c_str());
	std::string server_id(order_data->server_id()->begin(), order_data->server_id()->end());
	std::string client_order_id(order_data->order_id()->begin(), order_data->order_id()->end());
	std::string symbol(order_data->symbol()->begin(), order_data->symbol()->end());
	auto side = order_data->side();

	auto orderMgr = OrderManager::instance();
	orderMgr->addNewOrder(std::move(user_id), std::move(server_id), std::move(client_order_id), std::move(symbol)
		, order_data->preferred_venue_id(), side
		, order_data->price(), order_data->qty());
}
