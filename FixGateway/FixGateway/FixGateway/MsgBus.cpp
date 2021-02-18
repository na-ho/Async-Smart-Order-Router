#include "MsgBus.h"
#include "PreHeader.h"

using namespace FixGateway;

FixGateway::MsgBus::MsgBus()
{
}

FixGateway::MsgBus::~MsgBus()
{
    deInit();
}

void MsgBus::init()
{
	volatile bool done = false;
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
    natsConnection_Subscribe(&sub, conn, MSGBUS_REPORT, MsgBus::onMgs_report, NULL);
}

void FixGateway::MsgBus::publish(const char* subject, const char* data, int size)
{
    natsMsg* msg = NULL;
    natsMsg_Create(&msg, subject, NULL, data, size);
    natsConnection_PublishMsg(conn, msg);
    natsMsg_Destroy(msg);

}

//////////////////////////////////////

void MsgBus::onMgs_report(MSGBUS_NATS_PARAMETER)
{
}
