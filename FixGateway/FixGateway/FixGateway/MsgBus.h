#pragma once

#include <nats.h>

#include "PreHeader.h"

namespace FixGateway
{
	class MsgBus {
	public:
		MsgBus();
		~MsgBus();

		void init();
		void deInit();
		void subscribe();

		void publish(const char *subject, const char*data, int  size);
	private:
		static void onMgs_report(MSGBUS_NATS_PARAMETER);

	private:
		natsConnection* conn = NULL;
		natsSubscription* sub = NULL;
	};
}