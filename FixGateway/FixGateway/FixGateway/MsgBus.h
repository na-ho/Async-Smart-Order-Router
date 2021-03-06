#pragma once

#include <nats.h>
#include <string>

#include "PreHeader.h"

namespace FixGateway
{
	class MsgBus {
	public:
		MsgBus();
		~MsgBus();

		void init(const std::string &server_id);
		void destroy();
		void subscribe();

		void publish(const char *subject, const char*data, int  size);
	private:
		std::string getSubject(const char *subject);
		static void onMgs_report(MSGBUS_NATS_PARAMETER);

	private:
		natsConnection* _conn = NULL;
		natsSubscription* _sub_report = NULL;
		std::string _server_id;
	};
}