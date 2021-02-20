#include "MsgBus.h"
#include "HandlerOrder.h"
#include "HandlerMarketData.h"

void SOR::MsgBus::init() {
    volatile bool done = false;

    natsStatus s = natsConnection_ConnectTo(&_conn, NATS_DEFAULT_URL);
    initHandlers();

    if (s == NATS_OK)
    {
        subscribe();
    }
    nats_Sleep(100);

}

void SOR::MsgBus::initHandlers()
{
    _handlers.emplace_back(new HandlerOrder);
    _handlers.emplace_back(new HandlerMarketData);
}

void SOR::MsgBus::destroy()
{
    for (auto handler : _handlers) {
        handler->destroy();
        delete handler;
    }

    natsConnection_Destroy(_conn);
}

void SOR::MsgBus::sleep_forever()
{
    while (1) {
        nats_Sleep(1000);
    }
}

void SOR::MsgBus::subscribe()
{
    for (auto handler : _handlers) {
        handler->subscribe(_conn);
    }

    nats_Sleep(100);
}
