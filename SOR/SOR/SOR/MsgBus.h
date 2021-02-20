#pragma once

#include <vector>

#include <nats.h>
#include "Handler.h"

namespace SOR {
	class MsgBus {
	public:
		void init();
		void destroy();
		void sleep_forever();
	private:
		void initHandlers();
		void subscribe();

		natsConnection* _conn = NULL;
		//HandlerOrder _handleOrder;
		std::vector<Handler*> _handlers;

	};
}