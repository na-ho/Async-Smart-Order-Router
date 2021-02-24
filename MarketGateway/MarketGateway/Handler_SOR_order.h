#pragma

#include <nats.h>

#include "PreHeader.h"

#include "Handler.h"

namespace MarketGateway
{
	class Handler_SOR_order : public Handler {
	public:

		void destroy();
		void subscribe(natsConnection* conn);

		static void onMgs_sor_mg_order(MSGBUS_NATS_PARAMETER);

	private:
		natsSubscription* sub_fixg_sor_order = NULL;

	};
}