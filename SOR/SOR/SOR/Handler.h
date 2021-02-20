#pragma once

// Using polymorphism is not effect the performance(latency) due to affect on init and destroy only
namespace SOR
{
	class Handler {
	public:
		virtual void destroy() = 0;
		virtual void subscribe(natsConnection* conn) = 0;
	};
}

