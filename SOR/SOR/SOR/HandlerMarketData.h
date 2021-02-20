#pragma once

#include <nats.h>
#include "PreHeader.h"

#include "Handler.h"

namespace SOR
{
	class HandlerMarketData : public Handler {
	public:

		void destroy();
		void subscribe(natsConnection* conn);


	private:


	};
}