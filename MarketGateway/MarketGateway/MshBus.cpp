#include "MsgBus.h"
#include "Handler_SOR_order.h"

void MarketGateway::MsgBus::init() {
    volatile bool done = false;

    natsStatus s = natsConnection_ConnectTo(&_conn, NATS_DEFAULT_URL);
    initHandlers();

    if (s == NATS_OK)
    {
        subscribe();
    }
    nats_Sleep(100);

}

void MarketGateway::MsgBus::initHandlers()
{
    _handlers.emplace_back(new Handler_SOR_order);
}

void MarketGateway::MsgBus::destroy()
{
    for (auto handler : _handlers) {
        handler->destroy();
        delete handler;
    }

    natsConnection_Destroy(_conn);
}

void MarketGateway::MsgBus::sleep_forever()
{
    while (1) {
        nats_Sleep(1000);
    }
}

void MarketGateway::MsgBus::subscribe()
{
    for (auto handler : _handlers) {
        handler->subscribe(_conn);
    }

    nats_Sleep(100);
}
