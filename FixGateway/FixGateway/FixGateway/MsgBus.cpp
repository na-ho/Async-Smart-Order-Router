#include "MsgBus.h"
#include "PreHeader.h"

using namespace FixGateway;

MsgBus::MsgBus()
{
}

MsgBus::~MsgBus()
{
    deInit();
}

void MsgBus::init(const std::string& server_id)
{
	volatile bool done = false;
    _server_id = "." + server_id;

	natsStatus s = natsConnection_ConnectTo(&conn, NATS_DEFAULT_URL);

    if (s == NATS_OK)
    {
        subscribe();
    }
    nats_Sleep(100);
}

void MsgBus::deInit()
{
    natsSubscription_Destroy(sub);
    natsConnection_Destroy(conn);
}

void MsgBus::subscribe()
{
    natsConnection_Subscribe(&sub, conn, getSubject(MSGBUS_REPORT).c_str(), MsgBus::onMgs_report, NULL);
}

void MsgBus::publish(const char* subject, const char* data, int size)
{
    natsMsg* msg = NULL;
    natsMsg_Create(&msg, subject, NULL, data, size);
    natsConnection_PublishMsg(conn, msg);
    natsMsg_Destroy(msg);
}

//////////////////////////////////////

std::string MsgBus::getSubject(const char* subject)
{
    return subject + _server_id;
}

void MsgBus::onMgs_report(MSGBUS_NATS_PARAMETER)
{
}
