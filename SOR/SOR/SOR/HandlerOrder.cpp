#include <fmt/format.h>

#include "HandlerOrder.h"
#include "schemas/order_generated.h"

void SOR::HandlerOrder::destroy()
{
	natsSubscription_Destroy(sub_fixg_sor_order);
}

void SOR::HandlerOrder::subscribe(natsConnection* conn)
{
	natsConnection_QueueSubscribe(&sub_fixg_sor_order, conn, MSGBUS_FIXG_SOR_ORDER, MSGBUS_SOR_QUEUE_GROUP, HandlerOrder::onMgs_fixg_sor_order, NULL);
	natsSubscription_SetPendingLimits(sub_fixg_sor_order, -1, -1);

}

void SOR::HandlerOrder::onMgs_fixg_sor_order(MSGBUS_NATS_PARAMETER)
{
	auto data = natsMsg_GetData(msg);
	auto order_data = MsgSerialization::GetOrder_FIXG_SOR(data);

	fmt::print("recv {}\n", order_data->price());
}
