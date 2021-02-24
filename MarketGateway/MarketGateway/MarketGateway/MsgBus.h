#pragma once

#include <vector>

#include <nats.h>
#include "Handler.h"

namespace MarketGateway {
	class MsgBus {
	public:
		void init();
		void destroy();
		void sleep_forever();
	private:
		void initHandlers();
		void subscribe();

		natsConnection* _conn = NULL;
		std::vector<Handler*> _handlers;
	};
}