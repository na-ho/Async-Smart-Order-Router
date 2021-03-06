#pragma once

#include <nats.h>

#include "PreHeader.h"

#include "Handler.h"

namespace SOR
{
	class HandlerOrder : public Handler {
	public:

		void destroy();
		void subscribe(natsConnection* conn);

		static void onMgs_fixg_sor_order(MSGBUS_NATS_PARAMETER);

	private:
		natsSubscription* sub_fixg_sor_order = NULL;
		
	};
}