#pragma once

#include <nats.h>

namespace FeedHandler {
	class MsgBus {
	public:
		void init();
		void destroy();
		void sleep_forever();
	private:
		void initHandlers();
		void subscribe();

		natsConnection* _conn = NULL;
	};
}