#pragma once

namespace MarketGateway
{
	class Handler {
	public:
		virtual void destroy() = 0;
		virtual void subscribe(natsConnection* conn) = 0;
	};
}